# make 명령으로 컴파일합니다
# make clean으로 생성된 파일을 삭제합니다
#
# 컴파일러와 옵션 설정
CXX = g++
CXXFLAGS = -lSDL2 -lSDL2_ttf

# 대상 파일 이름
TARGET = game

# 소스 파일
SOURCES = main.cpp Block.cpp

# 기본 규칙
all: $(TARGET)

# 실행 파일 생성 규칙
$(TARGET): $(SOURCES)
	$(CXX) -o $(TARGET) $(SOURCES) $(CXXFLAGS)

# 정리 규칙
clean:
	rm -f $(TARGET)
