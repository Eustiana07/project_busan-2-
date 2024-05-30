#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define LEN_MIN 15
#define LEN_MAX 50
#define STM_MIN  0    // 마동석체력
#define STM_MAX  5
#define PROB_MIN 10   
#define PROB_MAX 90
#define AGGRO_MIN  0  // 어그로범위
#define AGGRO_MAX  5

// 마동석이동방향
#define MOVE_LEFT  1
#define MOVE_STAY  0

// 좀비의공격대상
#define ATK_NONE  0
#define ATK_CITIZEN  1
#define ATK_DONGSEOK  2

// 마동석 행동
#define ACTION_REST  0
#define ACTION_PROVOKE  1
#define ACTION_PULL  2

//어그로
#define AGGRO_MIN 1
#define AGGRO_MAX 5

//move
#define movement_MAX 1
#define movement_MIN 0
int main() {
    // 인트로
    printf("열차 길이와 시민과 좀비의 이동확률을 입력하여 시민을 탈출시키자!\n");
    // 열차 초기 상태 출력
    int trainLength = 0, citizenIndex = 0, madongindex = 0;
    int p = 0;
    int madongseokstamina = -1;
    int Ciagro = 1, Maagro = 1;
    while (trainLength < LEN_MIN || trainLength > LEN_MAX) {
        printf("train length(15~50)>> ");
        scanf_s("%d", &trainLength);
    }
    while (madongseokstamina < STM_MIN || madongseokstamina > STM_MAX) {
        printf("madongseok stamina(0~5)>> ");
        scanf_s("%d", &madongseokstamina);
    }
    while (p < PROB_MIN || p > PROB_MAX) {
        printf("percentile probability 'p'(10~90)>> ");
        scanf_s("%d", &p);
    }
    if (trainLength < LEN_MIN || trainLength > LEN_MAX || p < PROB_MIN || p > PROB_MAX) {
        printf("잘못 입력하셨습니다.\n");
        exit(0);
    }
    madongindex = trainLength - 3;
    for (int i = 0; i < trainLength; i++) {
        printf("#");
    }
    printf("\n#");
    for (int i = 0; i < trainLength - 7; i++) {
        printf(" ");
    }
    printf("C");
    printf("  Z");
    printf("M#\n");
    for (int i = 0; i < trainLength; i++) {
        printf("#");
    }
    printf("\n");
    printf("\n");
    printf("\n");
    // 시민과 좀비의 초기 위치 설정
    citizenIndex = trainLength - 6;
    int zombieIndex = trainLength - 4;

    int zombieMoveCount = 0; // 좀비의 이동 횟수를 카운트

    while (1) {
        // 시민 이동
        int citizenMove = rand() % 100;
        if (citizenMove < (100 - p)) {
            citizenIndex = (citizenIndex - 1 + trainLength) % trainLength; // 왼쪽으로 이동
        }
        //어그로
        if (Ciagro >= 5) {
            Ciagro = 5;
        }
        if (Maagro >= 5) {
            Maagro = 5;
        }
        // 좀비 이동
        if (zombieMoveCount % 2 == 0) { // 2번 주기마다 좀비 이동
            int zombieMove = rand() % 100;
            if (zombieMove < p) {
                if (Ciagro >= Maagro) {
                    zombieIndex = (zombieIndex - 1 + trainLength) % trainLength; // 왼쪽으로 이동
                }
                if (Ciagro < Maagro) {
                    zombieIndex = (zombieIndex + 1 + trainLength) % trainLength; // 왼쪽으로 이동
                }
            }

        }

        // 열차 상태 출력
        for (int i = 0; i < trainLength; i++) {
            printf("#");
        }
        printf("\n#");

        // 시민, 좀비 상태 출력
        for (int i = 0; i < trainLength; i++) {
            if (i == citizenIndex) {
                printf("C");
            }
            else if (i == zombieIndex)
                printf("Z");
            else if (i == madongindex)
                printf("M");
            else
                printf(" ");
        }
        printf("#");
        printf("\n");
        for (int i = 0; i < trainLength; i++) {
            printf("#");
        }
        printf("\n");
        if (citizenMove < (100 - p)) {
            Ciagro++;
            printf("citizen: %d -> %d (aggro: %d -. %d)\n", citizenIndex + 1, citizenIndex, Ciagro -1, Ciagro);
        }
        else if (citizenMove > (100 - p)) {
            Ciagro--;
            printf("citizen: stay %d (aggro: %d -. %d)\n", citizenIndex, Ciagro + 1, Ciagro);
        }

        if (zombieMoveCount % 2 == 0) {
            if (Ciagro >= Maagro) {
                printf("zombie: %d -> %d\n", zombieIndex + 1, zombieIndex);
            }
            if (Ciagro < Maagro) {
                printf("zombie: %d -> %d\n", zombieIndex - 1, zombieIndex );
            }
        }
        else if (zombieMoveCount % 2 != 0)
            printf("zombie: %d (cannot move)\n", zombieIndex);
        int mo = -1;
        while (mo < movement_MIN || mo > movement_MAX) {
            printf("madongseokmove(0:stay, 1:left)>> ");
            scanf_s("%d", &mo);
        }
        if (mo == 1) {
            madongindex--;
            Maagro++;
            printf("madongseok: %d > %d\n\n", madongindex + 1, madongindex);
        }
        if (mo == 0) {
            printf("madongseok: stay %d\n\n", madongindex);
            Maagro--;
        }
        //어그로
        if (Ciagro >= 5) {
            Ciagro = 5;
        }
        if (Maagro >= 5) {
            Maagro = 5;
        }

        if (citizenIndex == zombieIndex) {
            printf("GAME OVER!\nCitizen(s) has(have) been attacked by a zombie");
            exit(0);
        }
        if (citizenIndex == 0) {
            printf("SUCCESS!\ncitizen(s) escaped to the next train");
            exit(0);
        }
        printf("citizen does nothing.\n");
        printf("zombie attacked nobody.\n");
        int act = -1;
        if (madongindex != zombieIndex) {
            while (act < movement_MIN || act > movement_MAX) {
                printf("madongseokaction(0.rest, 1.provoke)>> ");
                scanf_s("%d", &act);
            }
            if (act == 0) {
                Maagro--;
                madongseokstamina++;
                printf("madongseokrests... \n");
                printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n\n", madongindex, Maagro + 1, Maagro, madongseokstamina - 1, madongseokstamina);
            }
            if (act == 1) {
                Maagro = 5;
            }
        }
        if (madongindex + 1 == zombieIndex) {
            while (act < 0 || act > 2) {
                printf("madongseokaction(0.rest, 1.provoke 2.pull)>> ");
                scanf_s("%d", &act);
            }
            if (act == 0) {
                Maagro--;
                madongseokstamina++;
                printf("madongseokrests... \n");
                printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n\n", madongindex, Maagro + 1, Maagro, madongseokstamina - 1, madongseokstamina);
            }
            if (act == 1) {
                Maagro = 5;
            }
            if (act == 2) {
                madongseokstamina--;
                Maagro++;
                Maagro++;
                int Dongseokpull = rand() % 100;;
                if (Dongseokpull < (100 - p)) {
                    printf("madongseokpulled zombie... Next turn, it can't move\n");
                    printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n\n", madongindex, Maagro - 2, Maagro, madongseokstamina + 1, madongseokstamina);
                    zombieMoveCount++;
                }
                if (Dongseokpull > (100 - p)) {
                    printf("madongseokfailed to pull zombie\n");
                    printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n\n", madongindex, Maagro - 2, Maagro, madongseokstamina + 1, madongseokstamina);
                }
            }
        }
        //어그로
        if (Ciagro >= 5) {
            Ciagro = 5;
        }
        if (Maagro >= 5) {
            Maagro = 5;
        }
        // 좀비 이동 횟수 증가
        zombieMoveCount++;
    }

    // 아웃트로

    return 0;
}
