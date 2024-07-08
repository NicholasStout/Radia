#include "radia.h"

/*
 * This class sets up the layouts and handles overarching commands and events
*/
Radia::Radia(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint);
    //set screen invisble and frameless

    QRect off = QApplication::desktop()->screenGeometry(this);
    int h, w;
    h = w = 0;
    for (QScreen * s : QGuiApplication::screens()) {
        QRect screen = s->availableGeometry();
        h+=screen.height();
        w+=screen.width();
    }
    //setMouseTracking(true);
    l = new Radia_Layout(this);
    //setLayout(l);
    upper = new Dial_Layout();
    QSize *size = new QSize(500, 500);

    //Get demensions for the launcher

    QRect *start = new QRect(QPoint(QCursor::pos().rx()-250,QCursor::pos().ry()-250), *size);
    printf("%d", QCursor::pos().rx());
    setGeometry(*start);
    setFixedHeight(500);
    setFixedWidth(500);
    l->setGeometry(*start);
    l->setUpperDial(upper);
}

void Radia::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    printf("%d,%d\n", event->pos().x(), event->y());
    upper->setAngle(event->pos());
    repaint();
}

bool Radia::eventFilter(QObject *object, QEvent *event)
{
    //qDebug() << event->type();
    return false;
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
            QApplication::quit();
        }
    }
}


Radia::~Radia()
{

}
