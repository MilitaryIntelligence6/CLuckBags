//
// Created by Administrator on 2020/11/24.
//
// !!!charset encoding == "GBK";(sorry about that "UTF-8" made console Garbled code)
//
// C99 标准;
// 编译环境 mingw-w64-8.1.0 i686 x86_64 posix dwarf
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define RECAST_TIMES 9999


/**
 * 获得单个红包;
 * @param moneyUpper
 * @return
 */
double getRandomLuckBag(double moneyUpper);

/**
 * 获得红包数组;
 * @param money
 * @param luckBagsNum
 * @return
 */
double* getLuckBag(double money, int luckBagsNum);

/**
 * 洗牌;
 * @param length 数组长度;
 * @return 映射数组;
 */
int* getShuffleMapper(int length);

/**
 * 交换;
 * @param foo
 * @param bar
 */
void swap(int *foo, int *bar);

/**
 * 通过value寻找key;
 * @param array
 * @param length
 * @param value
 * @return
 */
int findKeyByOnlyValue(int array[], int length, int value);

/**
 * 打印结果;
 * @param money
 * @param luckBagsNum
 */
void runLuckBags(double money, int luckBagsNum);

/**
 * 循环单元;
 */
void doLoop(void);

/**
 * 循环阻塞引擎;
 */
void start(void);


/**
 * 获得单个红包;
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
 * 获得红包数组;
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

    // 数组 index;
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
 * 洗牌;
 * @param length 数组长度;
 * @return 映射数组;
 */
int* getShuffleMapper(int length)
{
    int* mapper = malloc(sizeof(int) * length);

    // 生成顺序mapper映射;
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
 * 交换;
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
 * 通过value寻找key;
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
 * 打印结果;
 * @param money
 * @param luckBagsNum
 */
void runLuckBags(double money, int luckBagsNum)
{
    double* luckBagArray = getLuckBag(money, luckBagsNum);

    printf("\n%.2f元%d个红包的情况为:\n", money, luckBagsNum);

    printf("首次生成的红包: \n");
    int i;
    for (i = 0; i < luckBagsNum; ++i)
    {
        printf("红包%d = %.2f\t", i, *(luckBagArray + i));
    }

    int* mapper = getShuffleMapper(luckBagsNum);

    printf("\n\n乱序后的红包: \n");
    int j;
    int key;
    for (j = 0; j < luckBagsNum; ++j)
    {
        key = mapper[j];
        printf("乱序红包%d = %.2f\t", j, *(luckBagArray + key));
    }


    int realEarliestMaxKey = (int) luckBagArray[luckBagsNum];
    int nowEarliestMaxKey = findKeyByOnlyValue(mapper, luckBagsNum, realEarliestMaxKey);
    printf("\n\n最先生成的最大红包 红包%d = 乱序红包%d = %.2f\n", realEarliestMaxKey, nowEarliestMaxKey, luckBagArray[realEarliestMaxKey]);

    int realLatestMinKey = (int) luckBagArray[luckBagsNum + 1];
    int nowLatestMinKey = findKeyByOnlyValue(mapper, luckBagsNum, realLatestMinKey);
    printf("最后生成的最小红包 红包%d = 乱序红包%d = %.2f\n\n", realLatestMinKey, nowLatestMinKey, luckBagArray[realLatestMinKey]);

    free(luckBagArray);
    free(mapper);
}


/**
 * 循环单元;
 */
void doLoop(void)
{
    double money;
    int luckBagsNum;

    printf("请输入大于等于0.01元的金额, 最多保留两位小数到分\n>");
    scanf("%lf", &money);

    if (money < 0.01)
    {
        printf("ERROR:金额有误, 请重新输入!\n\n");
        doLoop();
        return;
    }

    printf("请输入整数红包个数:\n>");
    scanf("%d", &luckBagsNum);

    if (money * 100 < luckBagsNum)
    {
        printf("切分原子0.01元, 不能保证非0切分!请重新输入!\n\n");
        doLoop();
        return;
    }

    runLuckBags(money, luckBagsNum);
}


/**
 * 循环阻塞引擎;
 */
void start(void)
{
    int choice;
    do
    {
        doLoop();
        printf("\n是否继续，输入任意数字继续，输入 0 退出:\n");
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
