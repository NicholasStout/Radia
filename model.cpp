#include "model.h"
#include <string>
#include <stdlib.h>
#include <iostream>


/*
 * This is a model under the MVC design pattern, as well as acting as a factory for the fin Objects, which are their own controllers.
 * This objects creats fins based on what programs they are to run, as well as adding and hiding objects as they are needed.
 */

Model::Model(Radia_Layout * l, QWidget * parent) : QObject(nullptr)
{
    layout = l;
    p = parent;
    event_id = QEvent::registerEventType();
    populate_list();
    angle = &visible.front()->angle;
    prev_angle = int(*angle);
}

void Model::move_left()
{
    printf("Move left\n");
    fin * hold = visible.takeLast();
    layout->removeWidget(hold);
    hold->hide();
    fin_stack.push(hold);
    hold = fout_stack.pop();
    hold->offset = visible.first()->offset-layout->angle;
    visible.front()->setParent(hold);
    hold->setParent(p);
    hold->show();

    visible.prepend(hold);
    layout->addWidget(hold);
}
void Model::move_right()
{
    if (!fin_stack.isEmpty())
    {
        printf("Move right\n");
        fin * hold = visible.takeFirst();
        visible.first()->setParent(p);
        visible.first()->show();
        layout->removeWidget(hold);
        hold->hide();
        fout_stack.push(hold);
        hold = fin_stack.pop();
        hold->setParent(visible.back());
        hold->show();
        hold->offset = visible.back()->offset+layout->angle;
        visible.append(hold);
        layout->addWidget(hold);
    }
}
bool Model::event(QEvent * e)
{
    if (int(e->type()) == event_id)
    {
        //printf("%d, ", int(visible.first()->loc_angle) % 360);
        if (int(visible.last()->loc_angle)%360 > 180)
        {
            if (!fout_stack.isEmpty())
            {
                move_left();
            } else {
                visible.last()->angle = 180 - visible.last()->offset;
            }
            printf("pass\n");
            //prev_angle = int(*angle);
        } else if ((int(visible.first()->loc_angle) % 360) == 340)
        {
            printf("pass right\n");
            move_right();
            //prev_angle = int(*angle);
        }
        return true;
    }
    e->ignore();
    return false;
}

void Model::mouseMoveEvent(QMouseEvent *event)
{
    printf("Oh yeah, it's all coming together\n");
    event->ignore();
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
            dict.insert(parse.first(), parse.last());
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
                fin * f = new fin(head, event_id, this, img, dict.value("Exec"));
                f->offset = layout->angle*i;
                fin_stack.prepend(f);
                f->hide();
                head = f;
                i++;
            }
        }
    }
    printf("%d", layout->can_add_fin());
    while (layout->can_add_fin())
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
    return new QImage("/home/knil/Pictures/test.png");
}

Model::~Model(){}

