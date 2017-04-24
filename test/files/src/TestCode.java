public class TestCode implements Cloneable
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
	
	public int doSomething()
	{
		int var = -6;
		
		for(int k=0; k<field; k++)
		{
			field += var;
			var += k;
		}
		
		return field;
	}
	
	public int doSomethingElse(int value)
	{
		double d = getDouble();
		
		if(value > 0)
			d += doSomethingElse(value-1);
		
		d -= staticField;
		
		staticMethod();
		
		return (int)d;
	}
	
	public static void staticMethod()
	{
		System.out.println("In a static method!");
	}
	
	public Object clone()
	{
		Object obj = null;
		try
		{
			super.clone();
		}
		catch(java.lang.CloneNotSupportedException e)
		{
			System.out.println("Error");
		}
		return obj;
	}
}