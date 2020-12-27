//
// Created by Administrator on 2020/11/24.
//
// !!!charset encoding == "GBK";(sorry about that "UTF-8" made console Garbled code)
//
// C99 ��׼;
// ���뻷�� mingw-w64-8.1.0 i686 x86_64 posix dwarf
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define RECAST_TIMES 9999


/**
 * ��õ������;
 * @param moneyUpper
 * @return
 */
double getRandomLuckBag(double moneyUpper);

/**
 * ��ú������;
 * @param money
 * @param luckBagsNum
 * @return
 */
double* getLuckBag(double money, int luckBagsNum);

/**
 * ϴ��;
 * @param length ���鳤��;
 * @return ӳ������;
 */
int* getShuffleMapper(int length);

/**
 * ����;
 * @param foo
 * @param bar
 */
void swap(int *foo, int *bar);

/**
 * ͨ��valueѰ��key;
 * @param array
 * @param length
 * @param value
 * @return
 */
int findKeyByOnlyValue(int array[], int length, int value);

/**
 * ��ӡ���;
 * @param money
 * @param luckBagsNum
 */
void runLuckBags(double money, int luckBagsNum);

/**
 * ѭ����Ԫ;
 */
void doLoop(void);

/**
 * ѭ����������;
 */
void start(void);


/**
 * ��õ������;
 * @param moneyUpper
 * @return
 */
double getRandomLuckBag(double moneyUpper)
{
    double hundredTimesMoney = moneyUpper * 100;
    int hundredTimesLuckBag = rand() % (int) (hundredTimesMoney - 1) + 1;

    return (((double) hundredTimesLuckBag) / 100);
}


/**
 * ��ú������;
 * @param money
 * @param luckBagsNum
 * @return
 */
double* getLuckBag(double money, int luckBagsNum)
{
    double* luckBagsArray = malloc(sizeof(double) * (luckBagsNum + 2));

    const double minLuckBag = 0.01;
    double latestMinAmount = money;
    double earliestMaxAmount = 0;

    int minLuckAmountIndex = 0;
    int maxLuckAmountIndex = 0;

    // ���� index;
    int index = 0;

    double singleLuckBag;

    while (luckBagsNum)
    {
        if (luckBagsNum == 1)
        {
            singleLuckBag = money;
        } else
        {
            singleLuckBag = getRandomLuckBag(money - minLuckBag * luckBagsNum);
        }

        *(luckBagsArray + index) = singleLuckBag;

        if (singleLuckBag <= latestMinAmount)
        {
            latestMinAmount = singleLuckBag;
            minLuckAmountIndex = index;
        }

        if (singleLuckBag > earliestMaxAmount)
        {
            earliestMaxAmount = singleLuckBag;
            maxLuckAmountIndex = index;
        }

        money -= singleLuckBag;

        index++;
        luckBagsNum--;
    }

    *(luckBagsArray + index) = maxLuckAmountIndex;
    *(luckBagsArray + index + 1) = minLuckAmountIndex;

    return luckBagsArray;
}


/**
 * ϴ��;
 * @param length ���鳤��;
 * @return ӳ������;
 */
int* getShuffleMapper(int length)
{
    int* mapper = malloc(sizeof(int) * length);

    // ����˳��mapperӳ��;
    int j;
    for (j = 0; j < length; ++j)
    {
        mapper[j] = j;
    }

    int rdm1, rdm2;
    int tmp;
    int i;
    for (i = 0; i < RECAST_TIMES; i++)
    {
        rdm1 = rand() % length;
        rdm2 = rand() % length;

        if (rdm1 != rdm2)
        {
            tmp = mapper[rdm1];
            mapper[rdm1] = mapper[rdm2];
            mapper[rdm2] = tmp;
        }
    }
    return mapper;
}


/**
 * ����;
 * @param foo
 * @param bar
 */
void swap(int *foo, int *bar)
{
    int *tmp = foo;
    *foo = *bar;
    *bar = *tmp;
}


/**
 * ͨ��valueѰ��key;
 * @param array
 * @param length
 * @param value
 * @return
 */
int findKeyByOnlyValue(int array[], int length, int value)
{
    int i;
    for (i = 0; i < length; ++i)
    {
        if (array[i] == value)
        {
            return i;
        }
    }
    return -1;
}


/**
 * ��ӡ���;
 * @param money
 * @param luckBagsNum
 */
void runLuckBags(double money, int luckBagsNum)
{
    double* luckBagArray = getLuckBag(money, luckBagsNum);

    printf("\n%.2fԪ%d����������Ϊ:\n", money, luckBagsNum);

    printf("�״����ɵĺ��: \n");
    int i;
    for (i = 0; i < luckBagsNum; ++i)
    {
        printf("���%d = %.2f\t", i, *(luckBagArray + i));
    }

    int* mapper = getShuffleMapper(luckBagsNum);

    printf("\n\n�����ĺ��: \n");
    int j;
    int key;
    for (j = 0; j < luckBagsNum; ++j)
    {
        key = mapper[j];
        printf("������%d = %.2f\t", j, *(luckBagArray + key));
    }


    int realEarliestMaxKey = (int) luckBagArray[luckBagsNum];
    int nowEarliestMaxKey = findKeyByOnlyValue(mapper, luckBagsNum, realEarliestMaxKey);
    printf("\n\n�������ɵ������ ���%d = ������%d = %.2f\n", realEarliestMaxKey, nowEarliestMaxKey, luckBagArray[realEarliestMaxKey]);

    int realLatestMinKey = (int) luckBagArray[luckBagsNum + 1];
    int nowLatestMinKey = findKeyByOnlyValue(mapper, luckBagsNum, realLatestMinKey);
    printf("������ɵ���С��� ���%d = ������%d = %.2f\n\n", realLatestMinKey, nowLatestMinKey, luckBagArray[realLatestMinKey]);

    free(luckBagArray);
    free(mapper);
}


/**
 * ѭ����Ԫ;
 */
void doLoop(void)
{
    double money;
    int luckBagsNum;

    printf("��������ڵ���0.01Ԫ�Ľ��, ��ౣ����λС������\n>");
    scanf("%lf", &money);

    if (money < 0.01)
    {
        printf("ERROR:�������, ����������!\n\n");
        doLoop();
        return;
    }

    printf("�����������������:\n>");
    scanf("%d", &luckBagsNum);

    if (money * 100 < luckBagsNum)
    {
        printf("�з�ԭ��0.01Ԫ, ���ܱ�֤��0�з�!����������!\n\n");
        doLoop();
        return;
    }

    runLuckBags(money, luckBagsNum);
}


/**
 * ѭ����������;
 */
void start(void)
{
    int choice;
    do
    {
        doLoop();
        printf("\n�Ƿ�����������������ּ��������� 0 �˳�:\n");
        scanf("%d", &choice);
        printf("\n");
    } while (choice);
}


//int main(int argc, char *argv[])
int main()
{
    srand(time(NULL));

    printf("example:\n");
    runLuckBags(10, 10);
    start();
    return 0;
}
