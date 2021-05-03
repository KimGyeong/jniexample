public class JNI {
	static {
		System.loadLibrary("JNI");
	}

	private native int getNumber();

	public static void main(String[] args) {
		JNI jni = new JNI();

		System.out.println(jni.getNumber());
	}
}
