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
