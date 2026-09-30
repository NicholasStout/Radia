#include "test_populator.h"

test_populator::test_populator(int testNum) {num = testNum;}

const QList<FinDetails> test_populator::populateList()
{
    QList<FinDetails> ret;
    for(int i = 1; i <= num; i++)
    {
        FinDetails fd;
        fd.exec="test";
        fd.ico=QIcon();
        fd.name="test";
        ret.append(fd);
    }
    return ret;
}

QIcon test_populator::findIcon(QString ico) const
{
    return QIcon();
}
