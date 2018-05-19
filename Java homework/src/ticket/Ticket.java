package ticket;

public class Ticket {
	//private int tickets = 100;
	public static void main(String[] args){ 
		new MyThread().start(); 
		new MyThread().start(); 
		new MyThread().start(); 
		new MyThread().start(); 
	} 
	public static class MyThread extends Thread{ 
		//车票数量 
		static int tickets=100; 
		
		@Override 
		public void run() { 
			int sle = (int) (Math.random()*2000 + 1000);		
			try {
				Thread.sleep(sle);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			synchronized(this) {
				while(tickets>0){ 
					sle = (int) (Math.random()*1000);		
					try {
						Thread.sleep(sle);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					System.out.println(this.getName()+"卖出第【"+(100-tickets--)+"】张火车票"); 
					} 
				}
			
			} 
		} 
	}


/** * 使用Thread类模拟4个售票窗口共同卖100张火车票的程序 * * 没有共享数据，每个线程各卖100张火车票 * * @author jiqinlin * */ 
