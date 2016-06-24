import java.util.*;

class Main{
    private static boolean[][] nMat;
    public static void main(String[]args){
        Scanner cin = new Scanner(System.in);
        String line;
        int size = Integer.parseInt(cin.nextLine());
        nMat = new boolean[size][size];
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                nMat[i][j] = false;
            }
        } 
        for(;cin.hasNext();){
            int p1,p2;
            p1 = Integer.parseInt(cin.next());
            p2 = Integer.parseInt(cin.next());
            nMat[p1-1][p2-1] = true;
            nMat[p2-1][p1-1] = true;
        }
        
        int cMax = 0;
        for(int i=0;i<size;i++){
            for(int j=i+1;j<size;j++){
                int counter = 0;
                for(int k=0;k<size;k++){
                    if(nMat[i][k] && nMat[j][k]){
                        counter++;
                    }
                }
                if(cMax < counter) cMax = counter;
            }
        }
        System.out.println(cMax);
    }
}
