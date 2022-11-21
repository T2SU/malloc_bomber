# malloc_bomber

## 개요
- malloc이 어디서 얼마만큼의 메모리를 할당 받으려고 시도했는지 확인할 수 있습니다.
- malloc으로 메모리를 할당받으려고 할 때, 선택적으로 **메모리 할당 실패**를 **일부러** 유발시킬 수 있습니다.
  - 이 경우, errno는 ENOMEM이 설정되며, 반환 값은 NULL이 됩니다. (ENOMEM은 아직 구현 X)
- 현재 rd_route 라이브러리의 한계로, x86 및 x86_64 아키텍쳐에서만 동작합니다. (ARM(M1) 사용 불가)

## 사용법
1. 먼저 현재 git을 recursive 클론합니다. `git clone --recursive https://github.com/T2SU/malloc_bomber.git`
2. 클론된 디렉토리로 현재 디렉토리를 이동합니다. `cd malloc_bomber`
3. make를 사용해 빌드합니다. `make`
4. 실행하고 싶은 프로그램을 빌드된 malloct를 사용해 실행합니다. `./malloct [실행할 프로그램] (실행할 프로그램에 넘길 인자)`

### 실행시 주의
- **[실행할 프로그램] 자리에, 프로그램의 전체 경로를 적는 것을 권장합니다.**
  - libc의 `malloc`을 후킹하기 위해 dylib 동적 로딩을 활용하고 있습니다. 
  - 동적 로딩 경로는 `{현재디렉토리}/hooklib/testmalloc.dylib` 값이 기본으로 지정되어 있습니다.
  - `malloct` 바이너리를 다른 경로로 이동하거나, (컴파일 바이너리들이 존재하는) 현재 디렉토리가 아닌 곳에서 실행할 경우 `testmalloc.dylib` 라이브러리를 발견하지 못해 실행되지 않을 수 있습니다.


