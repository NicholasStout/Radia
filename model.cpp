#include "model.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fin.h>


/*
 * This is a model under the MVC design pattern, as well as acting as a factory for the fin Objects, which are their own controllers.
 * This objects creats fins based on what programs they are to run, as well as adding and hiding objects as they are needed.
 *
 * This will be removed in the future, replaced with *_dial_layout
 */

Model::Model(Radia_Layout * l, QWidget * parent) : QObject(nullptr)
{
    layout = l;
    p = parent;
    populate_list();
    angle = &visible.front()->angle;
    grab_angle = &visible.front()->grab_angle;
    res = &visible.front()->res;
    click_angle = 0;
    grab = 0;
}


void Model::set_angle(QPoint p) {
    double curr_angle = calc_angle(p, *res);
    double delta = curr_angle-*grab_angle;
    //printf("%d,%d ", p.x(), p.y());
    if (delta != 0) {
        *angle+=delta;
        *grab_angle=curr_angle;
    }
    if (*angle > 360 || *angle < 0) {
        *angle = int(*angle+360) % 360;
    }

    if (int(visible.last()->loc_angle)%360 >= 180)
    {
        if (!fout_stack.isEmpty())
        {
            move_left();
        } else {
            visible.last()->angle = 179.95 - visible.last()->offset;
        }
    } else if ((int(visible.first()->loc_angle) % 360) < 340 &&(int(visible.first()->loc_angle) % 360) > 180)
    {
        if (!fin_stack.isEmpty())
        {
            move_right();
        } else {
            visible.first()->angle = 340;
        }
    }
}

void Model::move_left()
{
    printf("Move left\n");
    Fin * hold = visible.takeLast();
    layout->removeWidget(hold);
    hold->hide();
    fin_stack.push(hold);
    hold = fout_stack.pop();
    //hold->offset = visible.first()->offset-layout->angle;
    visible.front()->setParent(hold);
    hold->setParent(p);
    hold->show();

    visible.prepend(hold);
    layout->addWidget(hold);
}
void Model::move_right()
{
    printf("Move right\n");
    Fin * hold = visible.takeFirst(); // take the fin we wish to remove and hold it
    if (hold->grab) {
        visible.first()->grab = 1;
    }
    visible.first()->setParent(p); // set the next fin to be the child of the MainWindow
    visible.first()->show(); //show it or they will all go away
    layout->removeWidget(hold); //remove the held fin
    hold->hide(); // hide it
    fout_stack.push(hold); // save it for later
    hold = fin_stack.pop(); //pop one off of the stack for the other end
    //hold->setParent(visible.back()); // set it's paraent to be the last fin
    hold->show(); // show it
    //hold->offset = visible.back()->offset+layout->angle; //set its angle
    visible.append(hold); // add it to the list of visible fins
    layout->addWidget(hold); //add it to the layout
    hold->grabMouse();
}

void Model::populate_list()
{
    QString base_uri = "/usr/share/applications/";
    QDir program_dir(base_uri);
    QStringList programs = program_dir.entryList(QStringList() << "*.desktop",QDir::Files);
    int i = 0;
    QWidget * head = p;
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
                    img = find_icon(ico);
                } else {
                    img = new QImage(ico);
                }
                Fin * f = new Fin(head, this, img, dict.value("Exec"));
                QObject::connect(f, &Fin::start, this, &Model::start_program);
                f->offset = layout->angle*i % 360;
                fin_stack.prepend(f);
                f->hide();
                head = f;
                i++;
            }
        }
    }
    while (layout->can_add_fin() && !fin_stack.isEmpty())
    {
        visible.append(fin_stack.pop());
        layout->addWidget(visible.last());
    }
    if (visible.isEmpty()) {
        throw 1;
    }
}

QImage* Model::find_icon(QString s) {
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

double Model::calc_angle(QPoint c, int res)
{
    int resolution = res;
    double x = c.x()-(resolution/2);
    double ang = rad_to_deg(atan(((c.y()*-1)+(resolution/2))/x)); //Mmmm Pi
    if (c.x() < resolution/2) {
        ang+=180;
    } else if (c.y() >= (resolution/2.0)) {
        ang+=360;
    }
    return ang;
}

void Model::start_program(QString s) {
    QProcess *process = new QProcess(p);
    QStringList lst = s.split(' ');
    QString prog = lst.takeFirst();
    qDebug() << "launching " << s;
    int result = process->startDetached(prog, lst);
    qDebug() << "result: " << result;
    QApplication::quit();
}

Model::~Model(){}

