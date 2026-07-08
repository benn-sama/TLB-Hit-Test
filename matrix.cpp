#include <ctime>
#include <iostream>

#define ROW_NUM 20480
#define COL_NUM 20480

char arr[ROW_NUM][COL_NUM];

double getElapsedTime(const timespec& start, const timespec& end) {
    double seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;

    // if nanoseconds rolled over (borrow a second)
    if (nanoseconds < 0) {
        seconds -= 1;
        nanoseconds += 1000000000;
    }

    return seconds + nanoseconds / 1e9;
}

void printStats(double elapsedTime) {
  std::cout << "Time to finish: " << elapsedTime << std::endl;
}

double writeRow() {
  struct timespec start_time, end_time;
  clock_gettime(CLOCK_REALTIME, &start_time);
  
  std::cout << "Writing rows started..." << std::endl;

  for (int i = 0; i < ROW_NUM; ++i) {
    for (int j = 0; j < COL_NUM; ++j) {
      arr[i][j] = 'a';
    }
  }

  std::cout << "Writing rows finished..." << std::endl;
  clock_gettime(CLOCK_REALTIME, &end_time);
  double elapseTime = getElapsedTime(start_time, end_time);
  return elapseTime;
}

double writeCol() {
  struct timespec start_time, end_time;
  clock_gettime(CLOCK_REALTIME, &start_time);
  
  std::cout << "Writing cols started..." << std::endl;

  for (int j = 0; j < COL_NUM; ++j) {
    for (int i = 0; i < ROW_NUM; ++i) {
      arr[i][j] = 'a';
    }
  }

  std::cout << "Writing cols finished..." << std::endl;
  clock_gettime(CLOCK_REALTIME, &end_time);
  double elapseTime = getElapsedTime(start_time, end_time);
  return elapseTime;
}

double readRow() {
  char reader;
  struct timespec start_time, end_time;
  clock_gettime(CLOCK_REALTIME, &start_time);
  
  std::cout << "Reading rows started..." << std::endl;

  for (int i = 0; i < ROW_NUM; ++i) {
    for (int j = 0; j < COL_NUM; ++j) {
      reader = arr[i][j];
    }
  }

  std::cout << "Reading rows finished..." << std::endl;
  clock_gettime(CLOCK_REALTIME, &end_time);
  double elapseTime = getElapsedTime(start_time, end_time);
  return elapseTime;
}

double readCol() {
  char reader;
  struct timespec start_time, end_time;
  clock_gettime(CLOCK_REALTIME, &start_time);
  
  std::cout << "Reading cols started..." << std::endl;

  for (int j = 0; j < COL_NUM; ++j) {
    for (int i = 0; i < ROW_NUM; ++i) {
      reader = arr[i][j];
    }
  }

  std::cout << "Reading cols finished..." << std::endl;
  clock_gettime(CLOCK_REALTIME, &end_time);
  double elapseTime = getElapsedTime(start_time, end_time);
  return elapseTime;
}

int main() {
  double averageTime = 0.0;

  // 10 times for writing row
  for (int i = 0; i < 10; ++i) {
    averageTime += writeRow();
  }
  averageTime /= 10;
  std::cout << "writing rows: " << averageTime << std::endl << std::endl;

  averageTime = 0.0;
  // 10 times for writing col
  for (int i = 0; i < 10; ++i) {
    averageTime += writeCol();
  }
  averageTime /= 10;
  std::cout << "writing cols: " << averageTime << std::endl << std::endl;

  averageTime = 0.0;
  // 10 times for reading row
  for (int i = 0; i < 10; ++i) {
    averageTime += readRow();
  }
  averageTime /= 10;
  std::cout << "reading row: " << averageTime << std::endl << std::endl;

  averageTime = 0.0;
  // 10 times for reading col
  for (int i = 0; i < 10; ++i) {
    averageTime += readCol();
  }
  averageTime /= 10;
  std::cout << "reading col: " << averageTime << std::endl << std::endl;
}