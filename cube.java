import java.util.*;

class Main{
    static final int size = 3;
    public static void main(String[] args){
        Scanner cin = new Scanner(System.in);
        String line;
        int[] num = new int[size*size*size];
        int count = 0;
        while(cin.hasNext()){
            line = cin.nextLine();
            line = line.replaceAll("\\[", "");
            line = line.replaceAll("\\]", "");
            String[] tmp = line.split(",", 0);
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    num[j+size*(i+size*count)] = Integer.parseInt(tmp[j+size*i]);
                }
            }
            count++;
        }
        int[] flag = new int[size*size*size];
        for(int i=0;i<size*size*size;i++){
            flag[i] = 2;
        }
        commitLowest(num, flag);
        commitZero(num, flag);
    	commitOne(num, flag);
    	System.out.println(countOkPattern(num, flag));
    }
    
    static void commitLowest(int[] num, int[] flag){
        for(int i=0;i<size*size;i++){
            flag[i] = num[i];
        }
    }
    
    static void commitZero(int[] num, int[] flag){
        for(int i=size*size;i<size*size*2;i++){
            if(num[i] == 0){
                flag[size*size*size*2-size*i-1] = 0;
                flag[size*size*size*2-size*i-2] = 0;
                flag[size*size*size*2-size*i-3] = 0;
            }
        }
        for(int i=size-1;i>=0;i--){
        	for(int j=0;j<size;j++){
	            if(num[(size*size-1-i)*size+j] == 0){
	            	flag[j+i*size*size] = 0;
	            	flag[size+j+i*size*size] = 0;
	            	flag[2*size+j+i*size*size] = 0;
	            }
        	}
        }
    }
	
	static void commitOne(int[] num, int[] flag){
		int count = 0;
		for(int i=size*size;i<size*size*2;i++){
            if(num[i] == 1){
                count += flag[size*size*size*2-size*i-1];
                count += flag[size*size*size*2-size*i-2];
                count += flag[size*size*size*2-size*i-3];
            }
			if(count == 2){
				flag[size*size*size*2-size*i-1] = (flag[size*size*size*2-size*i-1]==2)?
												1: flag[size*size*size*2-size*i-1];
	            flag[size*size*size*2-size*i-2] = (flag[size*size*size*2-size*i-2]==2)?
												1: flag[size*size*size*2-size*i-2];
	            flag[size*size*size*2-size*i-3] = (flag[size*size*size*2-size*i-3]==2)?
												1: flag[size*size*size*2-size*i-3];
			}
			count = 0;
        }
		
		count = 0;
        for(int i=size-1;i>=0;i--){
        	for(int j=0;j<size;j++){
	            if(num[(size*size-1-i)*size+j] == 1){
	            	count += flag[j+i*size*size];
	            	count += flag[size+j+i*size*size];
	            	count += flag[2*size+j+i*size*size];
	            }
        		if(count == 2){
					flag[j+i*size*size] = (flag[j+i*size*size] == 2)?
        								1: flag[j+i*size*size];
			        flag[size+j+i*size*size] = (flag[size+j+i*size*size] == 2)?
        								1: flag[size+j+i*size*size];
			        flag[2*size+j+i*size*size] = (flag[2*size+j+i*size*size] == 2)?
        								1: flag[2*size+j+i*size*size];
				}
        	}
        	count = 0;
        }
		
		for(int i=size*size*2;i<size*size*size;i++){
			if(flag[i] == 1){
				flag[i-size*size] = 1;
			}
		}
	}
	
	static int countOkPattern(int[] num, int[] flag){
		ArrayList<Integer> list = new ArrayList<Integer>();
		for(int i=0;i<size*size*size;i++){
			if(flag[i] != 2) continue;
			list.add(i);
		}
		
		//’Tõ
		int counter = 0;
		int tmp = 0, pos = 0;
		for(int i=0;i<Math.pow(2, list.size());i++){
			tmp = i;
			pos = 0;
			while(tmp > 0){
				flag[list.get(pos++)] = tmp % 2;
				tmp /= 2;
			}
			if(pos == list.size()){
				if(check(num, flag)){
					counter++;
				}
				continue;
			}
			for(int j=pos;j<list.size();j++){
				flag[list.get(j)] = 0;
			}
			if(check(num, flag)){
				counter++;
			}
		}
		return(counter);
    }
	
	static boolean check(int[] num, int[] flag){
		int sum = 0;
		
		for(int i=size*size;i<size*size*size;i++){
		    if((flag[i] == 1) && (flag[i-size*size] != 1)){
		        return(false);
		    }
		}
        for(int i=size*size;i<size*size*2;i++){
        	sum = 0;
            if(num[i] == 1){
                sum += flag[size*size*size*2-size*i-1];
                sum += flag[size*size*size*2-size*i-2];
                sum += flag[size*size*size*2-size*i-3];
            	if(sum == 0) return(false);
            }
        }
		sum = 0;
        for(int i=size-1;i>=0;i--){
        	for(int j=0;j<size;j++){
        		sum = 0;
	            if(num[(size*size-1-i)*size+j] == 1){
	            	sum += flag[j+i*size*size];
	            	sum += flag[size+j+i*size*size];
	            	sum += flag[2*size+j+i*size*size];
	            	if(sum == 0) return(false);
	            }
        	}
        }
		return(true);
	}
}
