import java.util.*;
class Main{
    public static void main(String[]args){
        Scanner cin=new Scanner(System.in);
        String line;
        for(;cin.hasNext();){
            line=cin.nextLine();
            System.out.println(calc(line));
        }
    }
    
    private static int calc(String line){
        boolean flag = false;
        int num = 999;
        for(int i = 0;i < line.length();i++){
            if(Integer.parseInt(line.substring(i, i+1)) == 0){
                flag = true;
            }
        }

        if( flag ){
            for(int i = 0;i < line.length();i++){
                if(Integer.parseInt(line.substring(i, i+1)) == 0) continue;
                num = (Integer.parseInt(line.substring(i, i+1)) > num)
                    ? num: Integer.parseInt(line.substring(i, i+1));
            }
        }else{
            num = 0;
            for(int i = 0;i < line.length();i++){
                num = (Integer.parseInt(line.substring(i, i+1)) < num)
                    ? num: Integer.parseInt(line.substring(i, i+1));
            }
        }
        return(num);
    }
}