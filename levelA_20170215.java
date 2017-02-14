import java.util.*;
import java.util.stream.Stream;

class Main{
    private static final int range = 1000000;
    private static final int[] list = new int[range];
    
    public static void main(String[]args){
        Scanner cin = new Scanner(System.in);
        ArrayList<Integer> lines = new ArrayList<Integer>();
        ArrayList<Integer> sols = new ArrayList<Integer>();
        String line = "";
        for(;cin.hasNext();){
            line = cin.nextLine();
            lines.add(Integer.parseInt(line));
            sols.add(0);
        }
        for(int i = 0; i < range; i++){
            list[i] = 2*i+1;
        }
        calc(lines, sols);
        
        Iterator<Integer> itr = sols.iterator();
        while(itr.hasNext()){
            System.out.println(itr.next());
        }
    }
    
    private static void calc(ArrayList<Integer> lines, ArrayList<Integer> sols){
        int num = -1;
        int j = 0;
        for(int i = 0; i < sols.size(); i++){
            num = lines.get(i);
            sols.set(i, count(num));
        }
    }

    private static int count(int num){
        int counter = 0;
        int start = num / 2;

        if(num % 2 == 0){
            return 0;
        }
        int m = (int)((2*range-1)/num);
        float dig = (float)m/2 - (int)(m/2);
        if(dig > 0) return((m/2)+1);
        return m/2;
    }
}
