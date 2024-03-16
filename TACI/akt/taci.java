

import java.util.Arrays;

public class taci implements Cloneable {
	private int id;
	private int g,h,f;
	private int[][] S;
	private int idcha;
	
	public int getIdcha() {
		return idcha;
	}

	public void setIdcha(int idcha) {
		this.idcha = idcha;
	}

	public Object clone()  throws CloneNotSupportedException{
		return super.clone();
	}
	
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public int getG() {
		return g;
	}
	public void setG(int g) {
		this.g = g;
	}
	public int getH() {
		return h;
	}
	public void setH(int[][] goal) {
		int count = 0;
		if(goal != null || S != null) {
			for(int i=0; i<goal.length; i++) {
				for(int j=0; j<goal[0].length; j++) {
					if(goal[i][j] != 0) {
						if(S[i][j] != goal[i][j]) {
							count ++;
						}
					}
				}
			}
		}
		this.h = count;
	}
	public int getF() {
		return f;
	}
	public void setF() {
		this.f = this.h+this.g;
	}
	public int[][] getS() {
		return S;
	}
	public void setS(int[][] s) {
		S = s;
	}

	@Override
	public String toString() {
		String kq = " S"+id+"\tg= " + g + ", h=" + h + ", f=" + f + "\n";
		for(int i = 0; i < S.length; i++) {
			for(int j = 0; j < S.length; j++) {
				kq += S[i][j]+" ";
			}
			kq +="\n";
		}
		return kq;
	}
	
	
}
