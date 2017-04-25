public class TestCode implements Runnable
{
	private int field = 2;
	private static int staticField = 5;
	
	public void empty() 
	{
	}
	
	public int getInt()
	{
		return 1;
	}
	
	public double getDouble()
	{
		return 1.618;
	}
	
	public double sum(int p1, double p2)
	{
		int a = 3;
		return p1 + p2 + a;
	}
	
	public void localVariables()
	{
		int a = 1;
		long b = 2;
		byte c = 3;
		float d = 5;
		double e = a + b - c * d;
	}
	
	public void loop()
	{
		for(int k=0; k<10; k++)
		{
			int a = 2*k;
			System.out.println(a);
		}
		
		int k = 1;
		while(k < 20)
		{
			k = 2*k+1;
		}
	}
	
	public void conditions()
	{
		int a = 2;
		if(5*(a + 1) < 3)
			a++;
		else
			a--;
		
		switch(a)
		{
			case 0: a += 0; break;
			case 1: a += 1; break;
			case 2: a += 2; break;
			default: a -= 1; break;
		}
		
		switch(a)
		{
			case 1: a += 1; break;
			case 8: a += 8; break;
			case 16: a += 16; break;
			default: a -= 1; break;
		}
	}
	
	public void arrays()
	{
		int[] intarr = new int[] {0, 2, 4};
		double[][] doublearr = new double[][] {{0, 1, 2}, {5, 6, 7}};
		Object[] objarr = new Object[]{4};
		
		int a = intarr[2];
		a += 2;
		intarr[0] = a;
	}
	
	public void callMethods()
	{
		Object obj = new Object();
		System.out.println(obj);
		
		empty();
		
		double d = getDouble();
		int i = getInt() + (int)d;
		byte b = (byte)i;
		int j = b;
		
		double s = sum(getInt(), getDouble());
		
		staticMethod();
		
		Runnable r = new TestCode();
		r.run();
	}
	
	@Override
	public void run()
	{
		System.out.println("In a call!");
	}
	
	public void fields()
	{
		field += 3;
		staticField *= 2;
	}

	public static void staticMethod()
	{
		System.out.println("In a static method!");
	}
}