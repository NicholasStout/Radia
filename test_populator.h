#ifndef TEST_POPULATOR_H
#define TEST_POPULATOR_H

#include "ipopulator.h"

class test_populator : public IPopulator
{
public:
    int num;
    test_populator(int testNum);
    const QList<FinDetails> populateList() override;
    QIcon findIcon(QString ico) const override;
};

#endif // TEST_POPULATOR_H
