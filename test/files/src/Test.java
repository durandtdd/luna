

public class Test
{
	// Field types
	private boolean booleanField = false;
	private byte byteField = (byte)0xf0;
	private char charField = 'a';
	private double doubleField = 3.1415926535;
	private float floatField = 3.1415f;
	private int intField = 0xf00df00d;
	private long longField = 0xf00df00ddeadbeefL;
	private short shortField = (short)0xf00d;
	
	private String stringField = "$£€";
	private int[][][] intTripleArrayField;
	private String[] stringArrayField = new String[] {"Hello, ", "world"};
	
	// Field flags
	private final int finalField = 123;
	private final double finalDoubleField = 1.618;
	private final String finalStringField = "Hello, world";
	private static int staticField = 456;
	private volatile int volatileField = 789;
	private transient int transientField = 987;
	public int publicField = 1;
	int packageField = 2;
	protected int protectedField = 3;
	private int privateField = 4;
	
	public enum Enum {EnumElement};
	private Enum enumField = Enum.EnumElement;
	
	// Methods parameters and type
	public void setIntMethod(int n) {}
	public void setStringMethod(String str) {}
	public void setArrayMethod(String[] array) {}

	public int getIntMethod() {return 0;}
	public String getStringMethod() {return "hello";}
	public String[] getArrayMethod() {return new String[] {};}
	
	public int doSomething(String[] array, int index, float value) {return index;}
	
	// Methods flags
	public void publicMethod() {}
	void packageMethod() {}
	protected void protectedMethod() {}
	private void privateMethod() {}
	public static void staticMethod() {}
	public final void finalMethod() {}
	public synchronized void synchronizedMethod() {}
	public void varargsMethod(Object... obj) {}
	public native void nativeMethod();	
	
	
	// Interfaces
	interface Interface
	{
		int interfaceField = 42;
		void interfaceMethod();
	}


	// Classes
	abstract class AbstractClass
	{
		public abstract void abstractMethod();
	}

	final class FinalClass extends AbstractClass implements Interface
	{
		public void interfaceMethod() {}
		public void abstractMethod() {}
	}
}

