// RUN: %clang_cc1 -triple arm64-apple-ios -fptrauth-calls -fptrauth-intrinsics -fblocks -emit-llvm %s  -o - | FileCheck %s

void (^blockptr)(void);

// CHECK: [[INVOCATION_1:@.*]] =  private constant { ptr, i32, i64, i64 } { ptr {{@.*}}, i32 0, i64 ptrtoint (ptr getelementptr inbounds ({ ptr, i32, i32, ptr, ptr }, ptr [[GLOBAL_BLOCK_1:@.*]], i32 0, i32 3) to i64), i64 0 }, section "llvm.ptrauth"
// CHECK: [[GLOBAL_BLOCK_1]] = internal constant { ptr, i32, i32, ptr, ptr } { ptr @_NSConcreteGlobalBlock, i32 1342177280, i32 0, ptr [[INVOCATION_1]],
void (^globalblock)(void) = ^{};

// CHECK-LABEL: define void @test_block_call()
void test_block_call() {
  // CHECK:      [[T0:%.*]] = load ptr, ptr @blockptr,
  // CHECK-NEXT: [[FNADDR:%.*]] = getelementptr inbounds {{.*}}, ptr [[T0]], i32 0, i32 3
  // CHECK-NEXT: [[T1:%.*]] = load ptr, ptr [[FNADDR]],
  // CHECK-NEXT: [[DISC:%.*]] = ptrtoint ptr [[FNADDR]] to i64
  // CHECK-NEXT: call void [[T1]](ptr noundef [[T0]]) [ "ptrauth"(i32 0, i64 [[DISC]]) ]
  blockptr();
}

void use_block(int (^)(void));

// CHECK-LABEL: define void @test_block_literal(
void test_block_literal(int i) {
  // CHECK:      [[I:%.*]] = alloca i32,
  // CHECK-NEXT: [[BLOCK:%.*]] = alloca [[BLOCK_T:.*]], align
  // CHECK:      [[FNPTRADDR:%.*]] = getelementptr inbounds nuw [[BLOCK_T]], ptr [[BLOCK]], i32 0, i32 3
  // CHECK-NEXT: [[DISCRIMINATOR:%.*]] = ptrtoint ptr [[FNPTRADDR]] to i64
  // CHECK-NEXT: [[SIGNED:%.*]] = call i64 @llvm.ptrauth.sign(i64 ptrtoint (ptr {{@.*}} to i64), i32 0, i64 [[DISCRIMINATOR]])
  // CHECK-NEXT: [[T0:%.*]] = inttoptr i64 [[SIGNED]] to ptr
  // CHECK-NEXT: store ptr [[T0]], ptr [[FNPTRADDR]]
  use_block(^{return i;});
}

struct A {
  int value;
};
struct A *createA(void);
