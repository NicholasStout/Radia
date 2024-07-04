#include "dial_layout.h"
//#include <QObject>

/* Sublayout to handle the dials on the top and bottom of the UI
 */

Dial_Layout::Dial_Layout(QWidget* parent) :
    QLayout(parent)
{
    angle = 35;
    populateList(parent);
}
void Dial_Layout::addItem(QLayoutItem *item)
{
    list.append(item);
}
void Dial_Layout::addFin(Fin *f)
{
    f->show();
    addItem(new QWidgetItem(f));
}
void Dial_Layout::removeFin(Fin *f)
{
    f->hide();
    for (QLayoutItem * i : list) {
        if (i->widget() == f) {
            list.removeOne(i);
        }
    }
}
void Dial_Layout::setGeometry(const QRect &r)
{
    if (r.width() == r.height())
    {
        QList<QLayoutItem *>::iterator itr = list.begin();
        Fin *f;
        for (; itr != list.end(); itr++) {
            f = (Fin *)(*itr)->widget();
            f->setGeometry(r);
            f->span = angle-5;
        }
    }
}
void Dial_Layout::setGeometry(const QRect &r, float ang)
{
    angle = ang;
    setGeometry(r);
}
QSize Dial_Layout::sizeHint() const
{
    return QSize(500, 500);
}
QLayoutItem * Dial_Layout::itemAt(int index) const
{
    if (index > 0 && index < list.size())
        return list.at(index);
    else
        return 0;
}
QLayoutItem * Dial_Layout::takeAt(int index)
{
    if (index > 0 && index < list.size())
        return list.takeAt(index);
    else
        return 0;
}
int Dial_Layout::count() const
{
    return list.size();
}
bool Dial_Layout::canAddFin()
{
    return (list.size() < (180/angle));
}

void Dial_Layout::setAngle(QPoint p)
{
    float curr_angle = calcAngle(p, res);
    float delta = curr_angle-grab_angle;
    //printf("%d,%d ", p.x(), p.y());
    if (delta != 0) {
        angle+=delta;
        grab_angle=curr_angle;
    }
    if (angle > 360 || angle < 0) {
        angle = int(angle+360) % 360;
    }

    if (int(visible.last()->loc_angle)%360 >= 180)
    {
        if (!fout_stack.isEmpty())
        {
            moveLeft();
        } else {
            visible.last()->angle = 179.95 - visible.last()->offset;
        }
    } else if ((int(visible.first()->loc_angle) % 360) < 340 &&(int(visible.first()->loc_angle) % 360) > 180)
    {
        if (!fin_stack.isEmpty())
        {
            moveRight();
        } else {
            visible.first()->angle = 340;
        }
    }

}

float Dial_Layout::calcAngle(QPoint c, int res)
{
    double x = c.x()-(res/2);
    double ang = radToDeg(atan(((c.y()*-1)+(res/2))/x)); //Mmmm Pi
    if (c.x() < res/2) {
        ang+=180;
    } else if (c.y() >= (res/2.0)) {
        ang+=360;
    }
    return ang;
}

void Dial_Layout::moveLeft()
{
    printf("Move left\n");
    Fin * hold = visible.takeLast();
    removeFin(hold);
    hold->hide();
    fin_stack.push(hold);
    hold = fout_stack.pop();
    //hold->offset = visible.first()->offset-layout->angle;
    visible.front()->setParent(hold);
    hold->setParent(p);
    hold->show();

    visible.prepend(hold);
    addFin(hold);
}

void Dial_Layout::moveRight()
{
    printf("Move right\nthis");
    Fin * hold = visible.takeFirst(); // take the fin we wish to remove and hold it
    if (hold->grab) {
        visible.first()->grab = 1;
    }
    visible.first()->setParent(p); // set the next fin to be the child of the MainWindow
    visible.first()->show(); //show it or they will all go away
    removeFin(hold); //remove the held fin
    hold->hide(); // hide it
    fout_stack.push(hold); // save it for later
    hold = fin_stack.pop(); //pop one off of the stack for the other end
    //hold->setParent(visible.back()); // set it's paraent to be the last fin
    hold->show(); // show it
    //hold->offset = visible.back()->offset+layout->angle; //set its angle
    visible.append(hold); // add it to the list of visible fins
    addFin(hold); //add it to the layout
    hold->grabMouse();
}
/*
 * This is to populate the list of installed programs to make fins for. This will be moved to a new class eventually.
 */
void Dial_Layout::populateList(QWidget* parent)
{
    QString base_uri = "/usr/share/applications/";
    QDir program_dir(base_uri);
    QStringList programs = program_dir.entryList(QStringList() << "*.desktop",QDir::Files);
    int i = 0;
    QWidget * head = parent;
    foreach (QString app, programs) {
        QFile file(base_uri+app);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            continue;
        }
        QMap<QString, QString> dict;
        while (!file.atEnd()){
            QStringList parse = QString(file.readLine()).trimmed().split('=');
            if (!dict.contains(parse.first())) {
                dict.insert(parse.first(), parse.last());
            }
        }
        if (dict.contains("NoDisplay")) {
            if (dict.value("NoDisplay") == "true") {
                continue;
            }
        }
        if (dict.contains("Terminal")){
            if (dict.value("Terminal")=="false")
            {
                QString ico = dict.value("Icon");
                QImage *img;
                QFileInfo path(ico);
                if (!(path.exists() && path.isFile())) {
                    img = findIcon(ico);
                } else {
                    img = new QImage(ico);
                }
                Fin * f = new Fin(head, this, img, dict.value("Exec"));
                QObject::connect(f, &Fin::start, this, &Dial_Layout::startProgram);
                f->offset = int(angle*i) % 360;
                fin_stack.prepend(f);
                f->hide();
                head = f;
                i++;
            }
        }
    }
    while (canAddFin() && !fin_stack.isEmpty())
    {
        visible.append(fin_stack.pop());
        addFin(visible.last());
    }
    if (visible.isEmpty()) {
        throw 1;
    }
}


QImage *Dial_Layout::findIcon(QString s)
{
    QString base_dir("/usr/share/icons/hicolor/");
    QDirIterator icon_it(base_dir, QStringList() << s+"*", QDir::Files, QDirIterator::Subdirectories); //Fix this later
    while(icon_it.hasNext()) {
        QString img = icon_it.next();
        if (img.contains(".svg")) {
            QImage *ret = new QImage(64,64, QImage::Format_ARGB32);
            QSvgRenderer renderer(img);
            QPainter paint(ret);
            renderer.render(&paint);
            //std::cout << img.toStdString();
            return ret;
        }

        return new QImage(img);
    }
    return new QImage("nothin");
}

void Dial_Layout::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    printf("%d,%d\n", event->pos().x(), event->y());
    setAngle(event->pos());
    p->update();
}

void Dial_Layout::startProgram(QString s) {
    QProcess *process = new QProcess(p);
    QStringList lst = s.split(' ');
    QString prog = lst.takeFirst();
    qDebug() << "launching " << s;
    int result = process->startDetached(prog, lst);
    qDebug() << "result: " << result;
    QApplication::quit();
}










