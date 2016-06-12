import java.util.*;
class Main{
    public static void main(String[]args){
        Scanner cin=new Scanner(System.in);
        Vector<String> slist = new Vector();
        for(;cin.hasNext();){
            String line = cin.nextLine();
            slist.add(line);
        }
        
        int nMax = Integer.parseInt(slist.elementAt(0));
        int cMax = Integer.parseInt(slist.elementAt(1));
        Vector<Card> clist = new Vector();
        for(int i=2;i<slist.size();i++){
            String[] dis = slist.elementAt(i).split(" ", 0);
            Card c = new Card(Integer.parseInt(dis[0]),
                Integer.parseInt(dis[1]));
            clist.add(c);
        }
        Calc calc = new Calc(nMax, cMax, clist);
        calc.execute();
        System.out.println(calc.getScore());
    }
}

class Calc{
    private int nMax;
    private int cMax;
    private int sMax;
    private Vector<Card> clist;
    public int counter;
    public Calc(int n, int c, Vector<Card> list){
        nMax = n;
        cMax = c;
        clist = list;
    }
    
    private int getConstN(int y, int num){
        if(nMax-y>=1){
            return(num);
        }
        return(0);
    }
    
    public void execute(){
        Sols sol[][] = new Sols[clist.size()+1][cMax+1];
        for(int i=0;i<=cMax;i++){
            sol[0][i] = new Sols( 0, 0);
        }
        for(int i=1;i<=clist.size();i++){
            Card card = new Card(clist.elementAt(i-1));
            for(int j=0;j<=cMax;j++){
                if(j < card.cost){
                    sol[i][j] = sol[i-1][j];
                }else{
                    Sols sc = sol[i-1][j-card.cost];
                    int s = getConstN(sc.num, card.score);
                    if(sc.score+s > sol[i-1][j].score){
                        Sols c = new Sols(s+sc.score, sc.num+1);
                        sol[i][j] = c;
                    }else{
                        sol[i][j] = sol[i-1][j];
                    }
                }
            }
        }
        sMax = sol[clist.size()][cMax].score;
    }
    public int getScore(){
        return(sMax);
    }
}

class Sols{
    public int score;
    public int num;
    public Sols(int s, int n){
        score = s;
        num = n;
    }
}

class Card{
    public int cost;
    public int score;
    public Card(int cost, int score){
        this.cost = cost;
        this.score = score;
    }
    public Card(Card c){
        cost = c.cost;
        score = c.score;
    }
}