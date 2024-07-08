#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <QMap>
#include <QObject>

class I_Input_Handler
{
public:
    QMap<QString, void *> map;
    I_Input_Handler();
    virtual ~I_Input_Handler();
    virtual void setMapping(QMap<QString, void *> map) = 0;

public slots:
    virtual void process(QEvent* e) = 0;
};

class KB_Input_Handler : public QObject, public I_Input_Handler
{
    Q_OBJECT
public:
    explicit KB_Input_Handler(QObject *parent = nullptr);

signals:
public slots:
    void process(QEvent* e);
};

class Mouse_Input_Handler : public QObject, public I_Input_Handler
{
    Q_OBJECT
public:
    explicit Mouse_Input_Handler(QObject *parent = nullptr);

signals:
public slots:
    void process(QEvent* e);
};
#endif // INPUT_HANDLER_H
