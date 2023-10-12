#pragma warning(disable:4996)
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
using namespace std;
int S1[4][4][2] = { {{0,1},{0,0},{1,1},{1,0}},
                 {{1,1},{1,0},{0,1},{0,0}},
                 {{0,0},{1,0},{0,1},{1,1}},
                 {{1,1},{0,1},{0,0},{1,0}} };
int S2[4][4][2] = { {{0,0},{0,1},{1,0},{1,1}},
                 {{1,0},{1,1},{0,1},{0,0}},
                 {{1,1},{0,0},{0,1},{1,0}},
                 {{1,0},{0,1},{0,0},{1,1}} };
void createkey(int k[11], int k1[9], int k2[9])
{
    int temp[11];
    temp[1] = k[3], temp[2] = k[5], temp[3] = k[2], temp[4] = k[7], temp[5] = k[4], temp[6] = k[10], temp[7] = k[1], temp[8] = k[9], temp[9] = k[8], temp[10] = k[6];
    int l[6], r[6];
    for (int i = 1; i <= 5; i++)
        l[i] = temp[i], r[i] = temp[i + 5];
    int x1, x2;
    x1 = l[1], x2 = r[1];
    for (int i = 2; i <= 5; i++)
        l[i - 1] = l[i], r[i - 1] = r[i];
    l[5] = x1;
    r[5] = x2;
    for (int i = 1; i <= 5; i++)
        temp[i] = l[i], temp[i + 5] = r[i];
    k1[1] = temp[6], k1[2] = temp[3], k1[3] = temp[7], k1[4] = temp[4], k1[5] = temp[8], k1[6] = temp[5], k1[7] = temp[10], k1[8] = temp[9];
    x1 = l[1], x2 = r[1];
    for (int i = 2; i <= 5; i++)
        l[i - 1] = l[i], r[i - 1] = r[i];
    l[5] = x1;
    r[5] = x2;
    for (int i = 1; i <= 5; i++)
        temp[i] = l[i], temp[i + 5] = r[i];
    k2[1] = temp[6], k2[2] = temp[3], k2[3] = temp[7], k2[4] = temp[4], k2[5] = temp[8], k2[6] = temp[5], k2[7] = temp[10], k2[8] = temp[9];
}
void f(int R[], int K[])
{
    int temp[9];
    temp[1] = R[4], temp[2] = R[1], temp[3] = R[2], temp[4] = R[3], temp[5] = R[2], temp[6] = R[3], temp[7] = R[4], temp[8] = R[1];
    for (int i = 1; i <= 8; i++)
        temp[i] = temp[i] ^ K[i];
    int s1[5], s2[5];
    for (int i = 1; i <= 4; i++)
        s1[i] = temp[i], s2[i] = temp[i + 4];
    int x1 = S1[s1[1] * 2 + s1[4]][s1[2] * 2 + s1[3]][0], x2 = S1[s1[1] * 2 + s1[4]][s1[2] * 2 + s1[3]][1];
    int x3 = S2[s2[1] * 2 + s2[4]][s2[2] * 2 + s2[3]][0], x4 = S2[s2[1] * 2 + s2[4]][s2[2] * 2 + s2[3]][1];
    R[1] = x2, R[2] = x4, R[3] = x3, R[4] = x1;
}
void Encode(int ming[9], int k1[], int k2[],int mi[],int k[])
{
    int temp[9];
    temp[1] = ming[2], temp[2] = ming[6], temp[3] = ming[3], temp[4] = ming[1], temp[5] = ming[4], temp[6] = ming[8], temp[7] = ming[5], temp[8] = ming[7];
    int L0[5], R0[5], L1[5], R1[5], L2[5], R2[5];
    for (int i = 1; i <= 4; i++)
        L0[i] = temp[i], R0[i] = temp[i + 4];
    memcpy(L1, R0, sizeof(L1));
    f(R0, k1);
    for (int i = 1; i <= 4; i++)
        R1[i] = L0[i] ^ R0[i];
    memcpy(R2, R1, sizeof(R2));
    f(R1, k2);
    for (int i = 1; i <= 4; i++)
        L2[i] = L1[i] ^ R1[i];
    temp[1] = L2[4], temp[2] = L2[1], temp[3] = L2[3], temp[4] = R2[1], temp[5] = R2[3], temp[6] = L2[2], temp[7] = R2[4], temp[8] = R2[2];
    bool a = true;
    for (int i = 1; i < 9; i++) {
        if (temp[i] != mi[i]) {
            a = false;
        }
    }
    if (a) {
        cout << "暴力破解获得的密钥是：";
        for (int i = 1; i < 11; i++) {
            cout << k[i];
        }
        cout << endl;
    }

    
}//对加密算法进行修改，当明文加密后的密文与输入密文相同时时输出密钥
void E(int k[]) {
    for (int i = 10; i > 0; i--) {
        if (k[i] == 2) {
            k[i] = 0;
            k[i - 1] += 1;
        }
    }
}//到2就进位，用数组表现二进制

int main()
{
     int k[11]={0}, k1[9], k2[9];
    int ming[9];
    printf("请输入明文:");
    for (int i = 1; i <= 8; i++)
        scanf("%1d", &ming[i]);
    printf("请输入密文:");
    int mi[9];
    for (int i = 1; i <= 8; i++)
        scanf("%1d", &mi[i]);
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1024; i++) {
        k[10] += 1;
        E(k);
        createkey(k, k1, k2);
        Encode(ming, k1, k2, mi, k);
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    // 计算运行时间（微秒为单位
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    std::cout << "程序运行时间: " << duration.count() << " 微秒" << std::endl;

    return 0;
}