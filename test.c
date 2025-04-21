#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_func(void* arg) {
    int id = *((int*)arg);
    printf("Thread %d: 開始\n", id);
    sleep(1); // 模擬的な処理時間
    printf("Thread %d: 終了\n", id);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    /* スレッド1の作成 */
    if (pthread_create(&thread1, NULL, thread_func, &id1) != 0) {
        perror("スレッド1作成失敗");
        return 1;
    }

    /* スレッド2の作成 */
    if (pthread_create(&thread2, NULL, thread_func, &id2) != 0) {
        perror("スレッド2作成失敗");
        return 1;
    }

    /* スレッド1の終了待機 */
    if (pthread_join(thread1, NULL) != 0) {
        perror("スレッド1待機失敗");
        return 1;
    }

    /* スレッド2のデタッチ */
    if (pthread_detach(thread2) != 0) {
        perror("スレッド2デタッチ失敗");
        return 1;
    }

    printf("メインスレッド: スレッド1の待機完了、スレッド2はデタッチ\n");
    sleep(2); // デタッチしたスレッドの終了を待つ
    return 0;
}
