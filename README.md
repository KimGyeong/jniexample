## JNI Example

### JNI
    - 주로 C, C++으로 작성된 코드를 JVM으로 호출하여 Java에서 사용할 수 있게끔 도와주는 라이브러리.

### 필요한 것
    - gcc or g++
    - Java JDK
    - terminal

### 순서
    1. Java 언어로 코드를 작성한다. 아래 코드는 `src > main > java`에 있는 JNI.java이다.
        ```java
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
        ```    
    2. Java 파일을 컴파일 한다. 이 때, 헤더파일을 생성해야 하므로 아래와 같은 명령어를 작성한다. `.`은 `src > main > java`와 같이 java 파일의 주소를 입력해야 한다.
    ```shell
    javac -h . JNI.java
    ```
    3. cpp파일을 생성한다. 이 때, 위에서 생성한 헤더파일이 갖고 있는 메소드와 동일한 메소드명을 기입해야 한다.
    ```cpp
    #include <jni.h>
    #include <stdio.h>
    #include "JNI.h"
    
    JNIEXPORT jint JNICALL Java_JNI_getNumber(JNIEnv *env, jobject jobj) {
    	return 1;
    }
    
    JNIEXPORT void JNICALL Java_JNI_printHelloWorld(JNIEnv *env, jobject jobj) {
    	printf("Hello World from C!\n");
    	return;
    }
    ```
    4. cpp 파일을 컴파일한다. 이 때, 아래와 같이 jdk의 라이브러리를 include 해야 한다. 각 컴퓨터에 맞게 주소를 기입해줘야 한다.
    ```shell
    g++ -c -I"C:\Program Files\Java\jdk1.8.0_281\include" -I"C:\Program Files\Java\jdk1.8.0_281\include\win32" JNI.cpp -o JNI.o
    ```
    5. 컴파일 결과로 나온 o 파일을 Java 파일과 동일한 위치에 옮겨준다.
    ```shell
    mv JNI.o ../java/JNI.o
    ```
    6. o 파일을 dll 파일로 공유 라이브러리로 만든다. 아래 명령어는 윈도우에서만 사용 가능하므로 유의하자.
    ```shell
    g++ -shared -o JNI.dll JNI.o -Wl,--add-stdcall-alias
    ```
    7. Java 파일을 실행해준다. library를 import 하는 옵션을 함께 명시해준다.
    ```shell
    java -cp . -Djava.library.path=./ JNI
    ```

### 삽질 목록
    1. 4번에서 Compile 에러가 발생했다.
        - `jni.h`를 임포트해줘야 한다.
        - 참고자료와 달리 `stdio.h`를 임포트하여 `printf`문을 사용하도록 변경했다.
        - 2번에서 컴파일하여 얻은 헤더 파일을 임포트해줘야 한다. 
    2. 4번에서 라이브러리의 위치를 찾지 못했다.
        - Windows에서 Java의 위치는 일반적으로 `C:\Program Files`인데, 띄어쓰기를 받아들이지 못했다. 처음 할 때, 시스템 환경변수인 `%JAVA_HOME%`으로 하다가 안돼서 주소를 모두 작성하고, 띄어쓰기를 받아들이지 못해서 따옴표를 추가하였다. 이후 시스템 환경변수 값에 따옴표를 추가하였다.
    3. 7번에서 library를 못찾는 에러가 발생했다.
        - 말그대로 사용해야 하는 라이브러리를 찾지 못한 것.
        - Java 코드에서 `System.loadLibrary`의 파라미터 값을 여러가지로 변경해보고, 커맨드의 라이브러리 주소도 여러가지로 변경해봤다.
        - 환장스럽게도 6번에서 공유 라이브러리를 만들 때, 결과물의 이름을 잘못 설정해서 발생했다.

### 참고 자료
    - https://www.baeldung.com/jni
    - https://mommoo.tistory.com/71
    - https://wiserloner.tistory.com/549