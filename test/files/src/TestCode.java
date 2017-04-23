public class TestCode
{
	private int field = 2;
	
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
}