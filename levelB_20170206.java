import java.util.*;
import java.util.stream.Stream;

class Main{
    public static void main(String[]args){
        Scanner cin = new Scanner(System.in);
        String line = "";
        for(;cin.hasNext();){
            line = cin.nextLine();
            System.out.println(subSeq(line));
        }
    }
    
    private static String subSeq(String line){
        StringBuilder ret = new StringBuilder(line);
        int pos = 0;
        int a, b;
        while(pos != ret.length()-1){
            a = Integer.parseInt("" + ret.charAt(pos));
            b = Integer.parseInt("" + ret.charAt(pos+1));
            if(judge( a, b, 1)){
                ret = ret.delete(pos, pos+2);
                pos = 0;
                continue;
            }
            pos++;
        }
        return(ret.toString());
    }
    
    private static boolean judge(int a, int b, int diff){
        if(Math.abs(a - b) == diff){
            return(true);
        }
        return(false);
    }
}
