#include "radia.h"

/*
 * This class sets up the layouts and handles overarching commands and events
*/
Radia::Radia(QWidget *parent) :
    QWidget(parent)
{
    //setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint);

    //set screen invisble and frameless

    //QRect off = QApplication::primaryScreen()->geometry();
    int h, w;
    h = w = 0;
    for (QScreen * s : QGuiApplication::screens()) {
        QRect screen = s->availableGeometry();
        h+=screen.height();
        w+=screen.width();
    }
    setMouseTracking(false);
    l = new radia_layout(this);
    //setLayout(l);
    QSize size = QSize(500, 500);

    //Get demensions for the launcher

    QRect start = QRect(QPoint(QCursor::pos().rx()-500,QCursor::pos().ry()-500), size);
    printf("%d", QCursor::pos().rx());
    setGeometry(start);
    start.setHeight(500);
    upper = new Dial(this, &start);
    setFixedHeight(500);
    setFixedWidth(500);
    l->setGeometry(start);
    l->setUpperDial(upper);
}

void Radia::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    printf("%d,%d\n", event->pos().x(), event->y());
    //upper->setAngle(event->pos());
    repaint();
}

//void Radia::paintEvent(QPaintEvent *)
//{
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    QColor c(127, 0, 127);
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(c);
//    QPainterPath center;
//    painter.drawPath(center);
//    painter.end();
//}

void Radia::mousePressEvent(QMouseEvent *event)
{
    qInfo();
    QApplication::quit();
}

void Radia::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        printf("Mouse release: %d,%d\n", event->x(), event->y());
        event->ignore();
    }
}

void Radia::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::ActivationChange) {
        if (!this->isActiveWindow()) {
            //qDebug() << "This fuckin thing is firing";
            QApplication::quit();
        }
    }
}

bool Radia::eventFilter(QObject *object, QEvent *event)
{
    if (auto *e = dynamic_cast<QInputEvent *>(event))
    {
        //qDebug() << event->type();
        return l->handleEvent(e);
    }
    return false;
}




Radia::~Radia()
{

}
