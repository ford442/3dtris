/*
 * Copyright 2017 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Modifications copyright (C) Otto Seiskari 2018
 */

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <jni.h>
#include "main_application.h"
#define JNI_METHOD(return_type,method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_xyz_osei_tris_JniInterface_##method_name
extern "C" {
namespace{
// maintain a reference to the JVM so we can use it later.
static JavaVM *g_vm=nullptr;
inline jlong jptr(MainApplication *native_application){
return reinterpret_cast<intptr_t>(native_application);
}
inline MainApplication *native(jlong ptr){
return reinterpret_cast<MainApplication *>(ptr);
}
}  // namespace

jint JNI_OnLoad(JavaVM *vm,void *){
g_vm=vm;
return JNI_VERSION_1_6;
}
JNI_METHOD(jlong,createNativeApplication)(JNIEnv *env,jclass,jobject j_asset_manager){
AAssetManager *asset_manager=AAssetManager_fromJava(env,j_asset_manager);
return jptr(new MainApplication(asset_manager));
}
JNI_METHOD(void,destroyNativeApplication)
(JNIEnv * , jclass , jlong native_application ) {
delete native(native_application);
}
JNI_METHOD(void,onPause)
(JNIEnv
*, jclass,
jlong native_application
) {
native(native_application)
->
OnPause();
}
JNI_METHOD(void,onResume)
(JNIEnv
*env, jclass,
jlong native_application,jobject
context,
jobject activity
) {
native(native_application)
->
OnResume(env,context,activity
);
}
JNI_METHOD(void,onGlSurfaceCreated)
(JNIEnv
*, jclass,
jlong native_application
) {
native(native_application)
->
OnSurfaceCreated();
}
JNI_METHOD(void,onDisplayGeometryChanged)
(JNIEnv
*, jobject,
jlong native_application,
int display_rotation,
int width,
int height
) {
native(native_application)
->
OnDisplayGeometryChanged(display_rotation,width,height
);
}
JNI_METHOD(jboolean,onGlSurfaceDrawFrame)(JNIEnv*,jclass,jlong
native_application) {
return static_cast
<jboolean>(
native(native_application)
->
OnDrawFrame()
? JNI_TRUE : JNI_FALSE);
}
JNI_METHOD(void,onTap)
(JNIEnv
*, jclass,
jlong native_application,jfloat
x,
jfloat y
) {
native(native_application)
->
OnTap(x,y
);
}
JNI_METHOD(void,onTouchUp)
(JNIEnv
*, jclass,
jlong native_application,jfloat
x,
jfloat y
) {
native(native_application)
->
OnTouchUp(x,y
);
}
JNI_METHOD(void,onScroll)
(JNIEnv
*, jclass,
jlong native_application,jfloat
x1,
jfloat y1,jfloat
x2,
jfloat y2,jfloat
dx,
jfloat dy
) {
native(native_application)
->
OnScroll(x1,y1,x2,y2,dx,dy
);
}
JNI_METHOD(jboolean,isTracking)(JNIEnv*,jclass,jlong
native_application) {
return static_cast
<jboolean>(
native(native_application)
->
IsTracking()
? JNI_TRUE : JNI_FALSE);
}
JNI_METHOD(jboolean,gameStarted)(JNIEnv*,jclass,jlong
native_application) {
return static_cast
<jboolean>(
native(native_application)
->
HasGameStarted()
? JNI_TRUE : JNI_FALSE);
}
JNI_METHOD(jboolean,gameOver)(JNIEnv*,jclass,jlong
native_application) {
return static_cast
<jboolean>(
native(native_application)
->
IsGameOver()
? JNI_TRUE : JNI_FALSE);
}
JNI_METHOD(void,restartGame)
(JNIEnv
*, jclass,
jlong native_application
) {
native(native_application)
->
RestartGame();
}
JNI_METHOD(jint,getScore)(JNIEnv*,jclass,jlong
native_application) {
return static_cast
<jint>(
native(native_application)
->
GetScore()
);
}
JNI_METHOD(jint,getArCoreInstallError)(JNIEnv*,jclass,jlong
native_application) {
return static_cast
<jint>(
native(native_application)
->
GetArCoreInstallError()
);
}
JNIEnv *GetJniEnv(){
JNIEnv*env;
jint result=g_vm->AttachCurrentThread(&env,nullptr);
return result == JNI_OK ? env :nullptr;
}
jclass FindClass(const char *classname){
JNIEnv*env=GetJniEnv();
return env->FindClass(classname);
}
}  // extern "C"
