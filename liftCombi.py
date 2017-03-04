class Parser_binary:
    def __init__(self, num, size):
        self.num = num-1
        self.size = size-1
    
    def genBin(self):
        s = 2**self.num
        counter = 0
        for x in range(s):
            s_bin = format(s-x-1, 'b').zfill(self.num)
            mem = self.calc(s_bin)
            if self.size >= mem: counter = counter+1
        print(counter)
    
    def calc(self, s_bin):
        counter = 0
        tmp = 0
        for i in range(len(s_bin)):
            if int(s_bin[i]) == 0: tmp = tmp + 1
            else:
                if tmp > counter: counter = tmp
                tmp = 0
        if tmp > counter: counter = tmp
        return counter

class Parser:
    
    def __init__(self, num, size):
        self.num = num
        self.size = size
        self.opt = [[0 for m in range(self.num)] for n in range(self.size)]
        self.opt[0] = [1 for m in range(self.num)]
        for n in range(self.size):
            self.opt[n][0] = 1
    
    def calcNum(self):
        for k in range(1, self.size):
            for n in range(k, self.size):
                self.opt[n][k] = 2**k
            for m in range(k+1, self.num):
                self.summations(m, k)

    def summations(self, m, n):
        for k in range(n+2):
            self.opt[n][m] += self.opt[n][m-k]

try:
    in_str = input().strip().upper().split(" ")
    m = int(in_str[0])
    n = int(in_str[1])
except EOFError:
    pass
p =  Parser(m, n)
p.calcNum()
print(p.opt[n-1][m-1])

