class GetAndGive:
    def __init__(self, m, n):
        self.get = m+1
        self.num = n+2
        
    def count(self):
        counter = 0
        if self.num >= self.get and 2*self.get >= self.num:
            counter = (self.num-self.get+1)/2
        if self.num >= 2*self.get and 3*self.get >= self.num:
            counter = (3*self.get-self.num+1)/2
        return int(counter)

try:
    in_str = input().strip().upper().split(" ")
    m = int(in_str[0])
    n = int(in_str[1])
except EOFError:
    pass
for i in range(1, m+1):
    for j in range(1, n+1):
        gag = GetAndGive(i, j)
        print(gag.count(), end="")
        del gag
    print()