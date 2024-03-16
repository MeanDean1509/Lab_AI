

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;

import javax.management.Query;
import javax.management.openmbean.OpenDataException;

public class akt {
	
	Scanner sc = new Scanner(System.in);
	
	Comparator<taci> comparator = (a,b) ->
	{
		if(a.getF() < b.getF())
			return -1;
		if(a.getF() > b.getF())
			return 1;
		return 0;
	};
	
	Queue<taci> open = new PriorityQueue<taci>(comparator);
	ArrayList<taci> close = new ArrayList<taci>();
	
	private int[][] goal;
	private int[][] initial;
	
//	public void Xuat() {
//		System.out.println("Goal");
//		for(int i = 0; i < goal.length; i++) {
//			for(int j = 0; j < goal.length; j++) {
//				System.out.print(goal[i][j]+" ");
//			}
//			System.out.println();
//		}
//		System.out.println("Initial state");
//		for(int i = 0; i < initial.length; i++) {
//			for(int j = 0; j < initial.length; j++) {
//				System.out.print(initial[i][j]+" ");
//			}
//			System.out.println();
//		}
//	}
	public void xuatOpen() {
		for (taci taci : open) {
			System.out.println(taci.toString());
		}
	}
	public void xuatClose() {
		for (taci taci : close) {
			System.out.println(taci.toString());
		}
	}
	
	public void test() {
		goal = new int[3][3];
		// {{1,2,3},{8,0,4},{7,6,5}};
		initial = new int[3][3];
		// {{2,8,3},{1,6,4},{7,0,5}};
		try {
            Scanner file = new Scanner(new File("taci.txt"));
            int n = file.nextInt();
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    initial[i][j] = file.nextInt();
                }
            }
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    goal[i][j] = file.nextInt();
                }
            }
            
            file.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
		taci a = new taci();
		a.setId(0);
		a.setS(initial);
		a.setG(0);
		a.setH(goal);
		a.setF();
		a.setIdcha(-1);
		open.offer(a);
	}
	
	public void Nhapmang() {
		System.out.println("Enter n(with or height of goal): ");
		int n = sc.nextInt();
		
		initial = new int[n][n];
		goal = new int[n][n];
		
		System.out.println("enter goal state with 0 as blank: ");
		for(int i =0; i<n;i++) {
			for(int j=0;j<n;j++) {
				goal[i][j] = sc.nextInt();
			}
		}
		
		System.out.println("Enter initial state: ");
		for(int i =0; i<n;i++) {
			for(int j=0;j<n;j++) {
				initial[i][j] = sc.nextInt();
			}
		}
		taci a = new taci();
		a.setId(0);
		a.setS(initial);
		a.setG(0);
		a.setH(goal);
		a.setF();
		a.setIdcha(-1);
		open.offer(a);
	}
	
	public void swap(int[][] a, int i,int j,int r, int l) {
		int temp = a[i][j];
		a[i][j] = a[r][l];
		a[r][l] = temp;
	}
	
	public void xuly() throws CloneNotSupportedException {
		int lanlap = 1;
		if(Arrays.deepEquals(open.peek().getS(), goal)) {
			System.out.println("Initial state is Goal state\n");
			System.out.println(open.peek().toString());
			return;
		}
		else {
			System.out.println("====================================================================");
			System.out.printf("Times: "+lanlap+" \nOpen\n[\n");
			for (taci taci : open) {
				System.out.print(taci.toString());
			}
			System.out.printf("]\n\nClose\n[");
			for (taci taci : close) {
				System.out.println(taci.toString());
			}
			System.out.println("]\n====================================================================");
			lanlap++;
		}
		while(open.peek() != null) {
			taci temp = open.poll();
			int[] vitri0 = layViTriCanDoi(temp.getS());
			if(vitri0 != null) {
				int dong = vitri0[0];
				int cot = vitri0[1];
				int trai = cot - 1;
				int phai = cot + 1;
				int tren = dong - 1;
				int duoi = dong + 1;
				
				if(tren >= 0) {
					int[][] S1 = copyarray(temp.getS());
					swap(S1, dong, cot, tren, cot);
					if(kiemtraOpen(S1) && kiemtraClose(S1)) {
						taci a1 =(taci) temp.clone();
						a1.setS(S1);
						xulydoi(a1);
						if(kiemtraClose(temp)) {
							close.add(temp);
						}
					}
				}
				if(duoi < temp.getS().length) {
					int[][] S2 = copyarray(temp.getS());
					swap(S2, dong, cot, duoi, cot);
					if(kiemtraOpen(S2) && kiemtraClose(S2)) {
						taci a2 = (taci) temp.clone();
						a2.setS(S2);
						xulydoi(a2);
						if(kiemtraClose(temp)) {
							close.add(temp);
						}
					}
				}
				if(trai >= 0) {
					int[][] S3 = copyarray(temp.getS());
					swap(S3, dong, cot, dong, trai);
					if(kiemtraClose(S3) && kiemtraOpen(S3)) {
						taci a3 = (taci) temp.clone();
						a3.setS(S3);
						xulydoi(a3);
						if(kiemtraClose(temp)) {
							close.add(temp);
						}
					}
				}
				if(phai < temp.getS()[0].length) {
					int[][] S4 = copyarray(temp.getS());
					swap(S4, dong, cot, dong, phai);
					if(kiemtraOpen(S4) && kiemtraClose(S4)) {
						taci a4 = (taci) temp.clone();
						a4.setS(S4);
						xulydoi(a4);
						if(kiemtraClose(temp)) {
							close.add(temp);
						}
					}
				}
				if(Arrays.deepEquals(temp.getS(), goal)) {
					ArrayList<taci> b = getPath(temp);
					System.out.print("RESULT\nS"+temp.getId()+" is goal state\nPath: ");
					for (int i=b.size()-1;i>=0;i--) {
						System.out.print("S"+b.get(i).getId()+" ");
					}
					System.out.println("\n");
					for(int i=b.size()-1;i>=0;i--) {
						System.out.println(b.get(i).toString());
					}
					break;
				}
				else {
					System.out.print("Lan lap: "+lanlap+" \nOpen\n[\n");
					for (taci taci : open) {
						System.out.print(taci.toString());
					}
					System.out.println("]\n");
					System.out.printf("Close\n[\n");
					for (taci taci : close) {
						System.out.print(taci.toString());
					}
					System.out.println("]\n====================================================================");
					lanlap++;
				}
				
			}
			else {
				System.out.println("Lỗi");
				return;
			}
		}
	}
	
	public int[][] copyarray(int[][] a){
		int[][] ketqua = new int[a.length][a[0].length];
		
		for(int i=0; i<a.length;i++) {
			for(int j=0; j<a.length;j++) {
				ketqua[i][j] = a[i][j];
			}
		}
		
		return ketqua;
	}
	
	public void xulydoi(taci a) {
		int g = a.getG();
		g++;
		int idcha = a.getId();
		a.setIdcha(idcha);
		int id = taoid(idcha);
		a.setId(id);
		a.setG(g);
		a.setH(goal);
		a.setF();
		
		if(kiemtraOpen(a) && kiemtraClose(a)) {
			open.offer(a);
		}
	}
	
	public boolean kiemtraOpen(taci a) {
		for (taci taci : open) {
			if(Arrays.deepEquals(a.getS(),taci.getS())) {
				return false;
			}
		}
		return true;
	}
	public boolean kiemtraClose(taci a) {
		for (taci taci : close) {
			if(Arrays.deepEquals(a.getS(),taci.getS())) {
				return false;
			}
		}
		return true;
	}
	public boolean kiemtraOpen(int[][] a) {
		for (taci taci : open) {
			if(Arrays.deepEquals(a,taci.getS())) {
				return false;
			}
		}
		return true;
	}
	public boolean kiemtraClose(int[][] a) {
		for (taci taci : close) {
			if(Arrays.deepEquals(a,taci.getS())) {
				return false;
			}
		}
		return true;
	}
	
	public int[] layViTriCanDoi(int[][] a) {
		for(int i=0; i<a.length; i++) {
			for(int j=0; j<a.length; j++) {
				if(a[i][j] == 0) {
					int[] t = {i,j};
					return t;
				}
			}
		}
		return null;
	}
	
	public int taoid(int id) {
		int max = id + 1;
		for (taci taci : close) {
			if(max <= taci.getId()) {
				max = taci.getId()+1;
			}
		}
		for (taci taci : open) {
			if(max <= taci.getId()) {
				max = taci.getId()+1;
			}
		}
		return max;
	}
	
	public ArrayList<taci> getPath(taci kq){
		ArrayList<taci> result = new ArrayList<taci>();
		result.add(kq);
		for (int i=close.size()-1; i >= 0;i--) {
			if(kq.getIdcha() == close.get(i).getId()) {
				result.add(close.get(i));
				kq = close.get(i);
			}
		}
		return result;
	}
}
