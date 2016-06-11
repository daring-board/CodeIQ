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
    public Calc(int n, int c, Vector<Card> list){
        nMax = n;
        cMax = c;
        clist = list;
    }
    public void execute(){
        int m[][][] = new int[clist.size()+1][cMax+1][nMax+1];
        for(int i=0;i<cMax;i++){
            for(int j=0;j<nMax;j++){
                m[0][i][j] = 0;
            }
        }
        int weight = 0;
        for(int i=1;i<=clist.size();i++){
            Card card = new Card(clist.elementAt(i-1));
            for(int j=0;j<=cMax;j++){
                for(int k=1;k<=nMax;k++){
                    if(j < card.cost){
                        m[i][j][k] = m[i-1][j][k];
                    }else{
                        if(m[i-1][j][k] < card.score+m[i-1][j-card.cost][k-1]){
                            m[i][j][k] = card.score+m[i-1][j-card.cost][k-1];
                        }else{
                            m[i][j][k] = m[i-1][j][k];
                        }
                    }
                }
            }
        }
        sMax = m[clist.size()][cMax][nMax];
    }
    public int getScore(){
        return(sMax);
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