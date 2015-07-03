#include <QString>
#include <QtTest>
#include <QCoreApplication>

class NcetestTest : public QObject
{
    Q_OBJECT

public:
    NcetestTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1_data();
    void testCase1();
};

NcetestTest::NcetestTest()
{
}

void NcetestTest::initTestCase()
{
}

void NcetestTest::cleanupTestCase()
{
}

void NcetestTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void NcetestTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(NcetestTest)

#include "tst_ncetesttest.moc"
