import numpy as np

class Search:
    size = 10
    flg = [0]*size
    num = [0]*size
    count = 0

    def checkSum(self) :
        sum = [0]*3
        sum[0] = self.num[0] + self.num[1] + self.num[2] + self.num[3]
        sum[1] = self.num[3] + self.num[4] + self.num[5] + self.num[6]
        sum[2] = self.num[6] + self.num[7] + self.num[8] + self.num[0]
        if sum[0] == sum[1] and sum[2] == sum[1]:
            self.count += 1

    def dfs(self, depth) :
        if depth == self.size-1 :
            self.checkSum()
            return
        for i in range(self.size) :
            if self.flg[i] != 1 :
                self.flg[i] = 1
                self.num[depth] = i+1
                self.dfs(depth+1)
                self.flg[i] = 0

    def printCount(self):
        print(self.count)

if __name__ == "__main__":
    print("count")
    search = Search()
    search.dfs(0)
    search.printCount()

