
public class basics { // 여기서 class 다음에 오는건 파일 이름과 같아야 실행되는거같음. Main.java면 class Main으로.
    public static int sum(int n, int m) { 
        return n+m;
    }

    public static void main(String[] args)
    {
        int i =20;
        int s;
        char a;

        s = sum(i,10);
        a ='?';
        System.out.println(a);
        System.out.println("Hello");
        System.out.println(s);
    }
}
