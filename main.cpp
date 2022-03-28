// ---------------------------------------------------------------------------
//                          Include Directives
// ---------------------------------------------------------------------------
#include <fstream>						// For open & save file
#include <iostream>						// Debug std::cin std::cout
#include "include/queue.hpp"			// int queue using linked list
#include "include/stack.hpp"			// int stack also using linked list
#include "include/colors.hpp"			// Define all colors need
#include "include/button.hpp"			// Button structures
#include "include/vertex.hpp"			// Vertex structures
#include "include/list_vertices.hpp"	// Manage all vertices
#include "include/helpers.hpp" 			// Basic functions & draw edges
#include "include/constants.hpp" 		// All constants go here
#include "include/global_variables.hpp"	// All Global variables
#define  MAX 10000
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// 							Draw all stuff here
// ---------------------------------------------------------------------------
struct CANH{
int u;
int v;
float value;
};
//CANH T[100];
int tongsocanh = 0;
///////////////////////
int D[20][20];
int S[20][20];

//////////////////////////
void drawWindow();
void drawWorkingZone();
void drawLimitZone();
void drawMenuZone();
void drawTextZone();
void drawMatrixZone();
void showSpeed();
void showAllButtons();
void refreshScreen();
void refreshGraph(int);
void initScreen();
void initializer();
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
//                          All algogrimth for menu
// ---------------------------------------------------------------------------
void Kruskal();
void Floyd();
/////
void SXkruskal(CANH E[],int tongsocanh);
void kruskal();
///////////////////
void floyd(int start, int stop);
/////
// ---------------------------------------------------------------------------
//                          		File
// ---------------------------------------------------------------------------
void open();
void save();
void quit();
void help();

// ---------------------------------------------------------------------------
//                          Graph editing functions
// ---------------------------------------------------------------------------
void addVertex();
void addEdges();
void renameVertex();
void deleteVertex();
void moveVertex();
void cleanGraph();

// ---------------------------------------------------------------------------
//                          Algogrimth helper
// ---------------------------------------------------------------------------
void removeVertex(int);
void removeRow(int);
void removeCol(int);
void removeLast();

void dfsTraveler(int);
void bfsTraveler(int);

void tarjanVisit(int, int *, int *, stack &, int &, int &, bool);
void tarjanResult(stack &, int, int);
int tarjanAlgo(bool, int remove = -1);

void recursiveHamilton(int, int *, bool &);
void resultHamilton(int *);
void continueHamilton(bool &);

bool isExistUndirectedEdge(int, int);
bool isExistDirectedEdge(int , int);
bool dfsToCheckConnected(bool (*)(int, int), int, int stop = -1);
void dfsToCheckKnot(int, int, bool *);

void calcDegree(int *, int *);
void sortDecendingDegree(int *);
bool isStronglyConnected();
bool isWeaklyConnected();
int eulerChecker();


// ---------------------------------------------------------------------------
//                          Graph helper functions
// ---------------------------------------------------------------------------
void drawEdge(int, int, int);
void drawAllEdges();
int chooseVertex(int, int skipReset = -1);
bool chooseStartVertex(int &, const char*, const char*);
bool chooseTwoVertices(int &, int &);
char getKey();
void adjustSpeed(char);
bool isEmptyGraph();
void showResultStack(stack &);
void showResultPathXY(double [], int, int);

// ---------------------------------------------------------------------------
//                          Keyboard editor functions
// ---------------------------------------------------------------------------
bool getInputChar(char *, int, bool (*)(char));
bool getInputWeight(float &);

// ---------------------------------------------------------------------------
//                          Texts: print, delete, set style
// ---------------------------------------------------------------------------
void setTextPrintStyle(int);
void printText(float);
void printText(const char*);
void deleteText(const char*);
template <typename Type>
void printTextWl(Type); // print text -> endl
template <typename Type>
void printTextWlb(Type); // endl -> print text

// ---------------------------------------------------------------------------
//                          		Menu
// ---------------------------------------------------------------------------
int findButton(int, int);
void switchMenuItem(int);
void menu();
void backToMenu();
// ---------------------------------------------------------------------------

int main()
{
    initializer();
	menu();
	closegraph();
	return EXIT_SUCCESS;
}
void drawWorkingZone()
{
	setfillstyle(SOLID_FILL, wZONE_COLOR);
	bar(wbLEFT, wTOP, wRIGHT, wBOTTOM);
	setcolor(LINE_COLOR);
	setlinestyle(SOLID_LINE, 1, 2);
	rectangle(wLEFT, wTOP, wRIGHT, wBOTTOM);
}
void drawLimitZone()
{
	setcolor(LIMIT_COLOR);
	setlinestyle(SOLID_LINE, 90, THICK_WIDTH);
	rectangle(wbLEFT + 2, wTOP + 2, wRIGHT - 2, wBOTTOM - 2);
}
void drawMenuZone()
{
	setbkcolor(BACKGROUND_COLOR);
	setusercharsize(1, 2, 1, 2);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(BLACK);
	outtextxy(5, mTOP - 20, "Menu");
	outtextxy(5, fTOP - 20, "File");
	outtextxy(5, aTOP - 20, "Adjacency matrix");
	setlinestyle(SOLID_LINE, 1, 2);
	setcolor(LINE_COLOR);
	rectangle(mLEFT, mTOP, mRIGHT, mBOTTOM);
	rectangle(fLEFT, fTOP, fRIGHT, fBOTTOM);
}
void drawTextZone()
{
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
	bar(tLEFT, tTOP, tRIGHT, tBOTTOM);
	setcolor(LINE_COLOR);
	setlinestyle(SOLID_LINE, 1, 2);
	rectangle(tLEFT, tTOP, tRIGHT, tBOTTOM);
	xCursor = xCURSOR; // Move cursor x to beginning
	yCursor = yCURSOR;
}
void drawMatrixZone()
{
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
	bar(aLEFT, aTOP, aRIGHT, aBOTTOM);
	setcolor(LINE_COLOR);
	setlinestyle(SOLID_LINE, 1, 2);
	rectangle(aLEFT, aTOP, aRIGHT, aBOTTOM);
	const int &n = listv.num + 1;
	if (n == 1) return;
	const float width = float(aRIGHT - aLEFT) / n;
	const float hight = float(aBOTTOM - aTOP) / n;
	setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
	setcolor(BLACK);
	setbkcolor(BACKGROUND_COLOR);
	settextjustify(LEFT_TEXT, CENTER_TEXT);
	if (n > aVERTEX_MAX_2)
	{
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
		outtextxy((aRIGHT + aLEFT) / 2, (aBOTTOM + aTOP) / 2, "KHONG THE HIEN THI.");
		return;
	}
	if (n > aVERTEX_MAX_1) settextstyle(SMALL_FONT, HORIZ_DIR, 4);
	else
	{
		setusercharsize(1, 2, 1, 2);
		settextstyle(BOLD_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	}
	setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
	char str[10];
	for (int i = 1; i < n; ++i)
	{
		line(aLEFT, aTOP + i * hight, aRIGHT, aTOP + i * hight);
		line(aLEFT + i * width, aTOP, aLEFT + i * width, aBOTTOM);
		outtextxy(ADJUST_TEXT_X, i * hight + ADJUST_TEXT_Y, listv.v[i - 1]->name);
		outtextxy(ADJUST_TEXT_X + i * width, ADJUST_TEXT_Y, listv.v[i - 1]->name);
		for (int j = 1; j < n; ++j)
			if (adjaGraph[i - 1][j - 1] != NO_EDGE_VALUE)
			{
				convertToChar(adjaGraph[i - 1][j - 1], str);
				outtextxy(ADJUST_TEXT_X + j * width, i * hight + ADJUST_TEXT_Y, str);
			}
	}
}
void showSpeed()
{
	char status[15];
	char speed[3];
	convertToChar((MAX_SPEED - delayRunTime) / 100, speed);
	strcpy(status, "Speed: ");
	strcat(status, speed);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
	bar(sLEFT, sTOP, sRIGHT, sBOTTOM);
	setbkcolor(BACKGROUND_COLOR);
	setusercharsize(1, 2, 1, 2);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	outtextxy(sLEFT, sTOP, status);
}
void drawWindow()
{
	setcolor(DOT_COLOR);
	setbkcolor(BACKGROUND_COLOR);
	setfillstyle(CLOSE_DOT_FILL, wZONE_COLOR);
	bar(0, 0, WINDOW_WIDTH, WINDOW_HIGHT);
}
void showAllButtons()
{
	for (int i = 0; i < NUM_OF_MENU; ++i)
	{
		menuButton[i].showNormalButton();
		showButtonIcon(menuButton, i);
	}
}
void initScreen()
{
	drawWindow();
	drawWorkingZone();
	drawTextZone();
	drawMenuZone();
	drawMatrixZone();
	showAllButtons();
	showSpeed();
}
void initializer()
{
	initwindow(WINDOW_WIDTH + 5, WINDOW_HIGHT + 10); //Remove +5, +10
	setwindowtitle("Graph Theory Demo 2.0");
	hwnd = GetActiveWindow();
	::SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE)&~WS_MAXIMIZEBOX);//&~WS_SIZEBOX
    initScreen();
    setMatrixTo(adjaGraph, NO_EDGE_VALUE);
}

/////////////////////////////////////
/////////////////////////////////

void Kruskal()
{
	if (isEmptyGraph()) return;
	kruskal();
	return backToMenu();
}
// lay ben lab04

void SXkruskal(CANH E[],int tongsocanh){
	CANH canhtam;
	for(int i = 0 ; i < tongsocanh   ; i++){
		for(int j = i + 1 ; j < tongsocanh ; j++)
			if(E[i].value > E[j].value){
			canhtam = E[i];
			E[i] = E[j];
			E[j] = canhtam;
		}
	}
}
void kruskal(){
	CANH T[100];
	int nT = 0;
	int Nhan[100];
	CANH DSCanh[100];
	for (int i=0;i<listv.num;i++){
		for( int j = 0; j<listv.num ; j++){
			if(adjaGraph[i][j] != NO_EDGE_VALUE){
				DSCanh[tongsocanh].u = i;
				DSCanh[tongsocanh].v = j;
				DSCanh[tongsocanh].value = adjaGraph[i][j];
				tongsocanh++;
				
			}
		}
	}
	SXkruskal(DSCanh, tongsocanh);
	
	for(int i=0; i< listv.num; i++){
		Nhan[i] = i;	
	}
	int iMin = 0;

	while(nT < listv.num - 1){
		if(iMin < tongsocanh){
			if((Nhan[DSCanh[iMin].u] != Nhan[DSCanh[iMin].v])){
			T[nT] = DSCanh[iMin];
			nT++;
			int giatri = Nhan[DSCanh[iMin].v];
			for (int j = 0; j < listv.num; j++){
				if (Nhan[j] == giatri)
				Nhan[j] = Nhan[DSCanh[iMin].u];
			}
			}
		iMin++;
		}
		else{
		break;
		}
	}
	int Tong = 0;
	if(nT != listv.num - 1) 
		MessageBox(hwnd, "Do thi khong lien thong", "Loi", MB_APPLMODAL | MB_ICONERROR);
	else {
//		printf("Do thi lien thong \n");
//		printf ("Cay khung nho nhat cua do thi la \n");
		setTextPrintStyle(TEXT_COLOR);
		printTextWl("Cac khung do thi tim duoc:");
		for (int i = 0; i < nT; i++){
			drawEdge(T[i].u, T[i].v, EDGE_VISTED_COLOR);
			setTextPrintStyle(TEXT_COLOR);
			printText("(");
			printText(listv.v[T[i].u]->name);
			printText(",");
			printText(listv.v[T[i].v]->name);
			printText(");");
//				printText(listv.v[T[i].u+1]->name);
//				printText(listv.v[T[i].v+1]->name);
			delay(delayRunTime);
			delay(delayRunTime);
			delay(delayRunTime);
//			printf ("(%d,%d), ", T[i].u, T[i].v);

			Tong += T[i].value;

		}
	}
	
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tong gia tri cua cay khung la: ");
	printText(Tong);
	
	//	printf ("\nTong gia tri cua cay khung la %d\n",TongTrongSoCuaCayKhung);
	

}


//////////////////////////
/////////////////////////
void Floyd(){
	if (isEmptyGraph()) return;
	int start, stop;
	if (chooseTwoVertices(start, stop)){
		setTextPrintStyle(TEXT_COLOR);
		printTextWl("Khoi chay thuat toan Floyd:");
		floyd(start, stop);
	}
	
	return backToMenu();
}



void floyd(int start, int stop){
	int i, j, k;
	
	
	for(int i=0; i<listv.num;i++){
		for(int j=0; j<listv.num;j++){
			D[i][j]=adjaGraph[i][j];
			if(D[i][j]==0 && i!=j){
				D[i][j]=MAX;
			}
		}
	}
	for(int i=0; i<listv.num;i++){
		for(int j=0; j<listv.num;j++){
			if(D[i][j]==MAX) S[i][j]=0;
			else S[i][j]=j;
		}
	}
	for(int k=0; k<listv.num;k++){
		for(int i=0; i<listv.num;i++){
			for(int j=0;j<listv.num;j++){
				if(D[i][k]!= MAX && D[i][j]>(D[i][k]+D[k][j])){
					D[i][j]=D[i][k]+D[k][j];
					S[i][j]=S[i][k];
				}
				
			}
		}
	}
 	
	if (D[start][stop] >= MAX) {
	printTextWl("Khong co duong di");
	}
 	else {
 		int s = start ;
 		printText("Duòng di: ");
 		printText(listv.v[start]->name);
  		while (start != stop) {
  			drawEdge(start, S[start][stop] , EDGE_VISTED_COLOR);
  			setTextPrintStyle(TEXT_COLOR);
  			printText("->"); 
  			printText(listv.v[start+1]->name);
			start = S[start][stop];
			delay(delayRunTime);
			delay(delayRunTime);
			delay(delayRunTime);
  		}
		printTextWl(" ");
		printText("Có do dài là: "); printText(D[s][stop]);
	}	
	
}
////////////////////////
////////////////////////

inline void removeRow(int row)
{
	for (int i = row; i < listv.num - 1; ++i)
		for (int j = 0; j < listv.num; ++j)
			adjaGraph[i][j] = adjaGraph[i + 1][j];
}
inline void removeCol(int col)
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = col; j < listv.num - 1; ++j)
			adjaGraph[i][j] = adjaGraph[i][j + 1];
}
inline void removeLast()
{
	const int &LAST = listv.num - 1;
	for (int i = 0; i < listv.num; ++i) //Remove last row & last column
	{
		adjaGraph[LAST][i] = NO_EDGE_VALUE;
		adjaGraph[i][LAST] = NO_EDGE_VALUE;
	}
}
void removeVertex(int v)
{
	removeCol(v);
	removeRow(v);
	removeLast();
}

void calcDegree(int *degIn, int *degOut)
{
	for (int i = 0; i < listv.num; ++i)
	{
		degOut[i] = degIn[i] = 0;
		for (int j = 0; j < listv.num; ++j)
		{
			if (adjaGraph[i][j] != NO_EDGE_VALUE) ++degOut[i];
			if (adjaGraph[j][i] != NO_EDGE_VALUE) ++degIn[i];
		}
	}
}
void sortDecendingDegree(int *order)
{
	const int &NUM = listv.num;
	int degIn[NUM];
	int degOut[NUM];
	calcDegree(degIn, degOut);
	setArrayTo(trace, NUM, 1);
	for (int i = 0; i < NUM; ++i)
	{
		int maxDegree = -1;
		int maxPos;
		for (int j = 0; j < NUM; ++j)
		{
			if (trace[j] && degOut[j] + degIn[j] > maxDegree)
			{
				maxDegree = degOut[j] + degIn[j];
				maxPos = j;
			}
		}
		order[i] = maxPos;
		trace[maxPos] = 0;
	}
}
int tarjanAlgo(bool showResult, int remove)
{
	const int &NUM = listv.num;
	int disc[NUM];
	int low[NUM];
	setArrayTo(disc, NUM, 0);
	setArrayTo(trace, NUM, 1);
	int count(0), components(0);
	stack s;
	if (remove != -1)
	{
		disc[remove] = 1; // ignore remove
		trace[remove] = 0; // ignore remove
	}
	for (int i = 0; i < NUM; ++i)
		if (disc[i] == 0) tarjanVisit(i, disc, low, s, count, components, showResult);
	return components;
}
void tarjanVisit(int u, int *disc, int *low, stack &s, int &count, int &components, bool callTarjanResult)
{
	low[u] = disc[u] = ++count;
	s.push(u);
	int v;
	for (v = 0; v < listv.num; ++v)
		if (trace[v] != 0 && adjaGraph[u][v] != NO_EDGE_VALUE)
			if (disc[v] != 0)
				low[u] = min(low[u], disc[v]);
			else
			{
				tarjanVisit(v, disc, low, s, count, components, callTarjanResult);
				low[u] = min(low[u], low[v]);
			}
	if (disc[u] == low[u])
	{
		++components;
		if (callTarjanResult)
			tarjanResult(s, u, components);
		else
			do
			{
				v = s.pop();
				trace[v] = 0;
			} while (v != u);
	}
}
void tarjanResult(stack &s, int stop, int components)
{
	setTextPrintStyle(TEXT_COLOR);
	printText(components);
	printText(":(");
	int v;
	do
	{
		v = s.pop();
		trace[v] = 0;
		listv.v[v]->show(VERTEX_MORE_COLOR[components]);
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText(listv.v[v]->name);
		printText(",");
		
	} while (v != stop);
	deleteText(",");
	printText(") ");
}

inline bool isExistUndirectedEdge(int v1, int v2)
{
	return (adjaGraph[v1][v2] != NO_EDGE_VALUE || adjaGraph[v2][v1] != NO_EDGE_VALUE);
}
inline bool isExistDirectedEdge(int v1, int v2)
{
	return (adjaGraph[v1][v2] != NO_EDGE_VALUE);
}
bool dfsToCheckConnected(bool (*checkEdge)(int , int ), int start, int stop)
{
	setArrayTo(trace, listv.num, 0);
	stack s;
	s.push(start);
	trace[start] = 1;
	int numOfCheckedVertex(0);
	while (!s.isEmpty())
	{
		start = s.pop();
		if (start == stop) return 1;
		++numOfCheckedVertex;
		for (int i = 0; i < listv.num; ++i)
			if (trace[i] == 0 && checkEdge(start, i))
			{
				trace[i] = 1;
				s.push(i);
			}
	}
	return (numOfCheckedVertex == listv.num);
}
void dfsToCheckKnot(int start, int stop, bool *mark)
{
	trace[start] = 1;
	if (start == stop) // found path start->stop
		for (int i = 0; i < listv.num; ++i) // update mark
			mark[i] = trace[i] && mark[i];
	else
	{
		for (int i = 0; i < listv.num; ++i)
			if (trace[i] == 0 && adjaGraph[start][i] != NO_EDGE_VALUE)
				dfsToCheckKnot(i, stop, mark);
	}
	trace[start] = 0;
}
inline bool isStronglyConnected()
{
	return (tarjanAlgo(0) == 1); // Strong Connected Components = 1
}
inline bool isWeaklyConnected()
{
	return dfsToCheckConnected(isExistUndirectedEdge, 0);
}
int eulerChecker()
{
	int returnValue = NOT_EXIST_EULER;
	int degIn[listv.num];
	int degOut[listv.num];
	calcDegree(degIn, degOut);
	int u(0), v(0), count(0);
	for (int i = 0; i < listv.num; ++i)
		if (degIn[i] != degOut[i])
			(++count == 1) ? u = i : v = i;
	if (isStronglyConnected() && count == 0)
		returnValue = EXIST_EULER;
	else
		if (isWeaklyConnected() && count == 2)
		{
			const int s1 = abs(degOut[u] - degIn[u]);
			const int s2 = abs(degIn[v] - degOut[v]);
			if (s1 == 1 && s2 == 1)
				(degOut[u] < degOut[v]) ? returnValue = v : returnValue = u; // return start's vertex haft euler 
		}
	return returnValue;
}
void copyToMutilGraph(bool gr[][MAX_VERTEX]) // use for euler
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			gr[i][j] = (adjaGraph[i][j] != NO_EDGE_VALUE);
}
bool isNegativeWeight()
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			if (adjaGraph[i][j] != NO_EDGE_VALUE && adjaGraph[i][j] < 0)
				return 1;
	return 0;
}

bool isNegativeCycle(double *dist)
{
	const int &NUM = listv.num;
	for (int i = 0; i < NUM; ++i)
		for (int j = 0; j < NUM; ++j)
			if (adjaGraph[j][i] != NO_EDGE_VALUE && dist[j] != MAX_EDGE_VALUE 
				&& dist[i] > dist[j] + adjaGraph[j][i])
				return true;
	return false;
}


void open()
{

	if (listv.num > 0 && MessageBox(hwnd,"Dang ton tai do thi\
	\nBan co muon xoa va mo do thi moi khong?","Thong bao",
	MB_APPLMODAL | MB_ICONWARNING | MB_YESNO) == IDNO) return;
	OPENFILENAME file;
	char fileName[MAX_PATH] = "\0";
//	_getcwd(fileName, MAX_PATH);
	ZeroMemory(&file, sizeof(file));
	file.lStructSize = sizeof(file);
	file.lpstrFile = fileName;
	file.nMaxFile = sizeof(fileName);
	file.lpstrFilter = (FILE_FILTER);
	file.nFilterIndex = 1;
	file.hwndOwner = hwnd;
	file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_READONLY;
	bool error = 0;
	if (GetOpenFileName(&file) == 1)
	{
		while (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
		std::ifstream openFile(fileName);
		int num;
		if ((openFile >> num) && openFile.good())
		{
			listv.clear();
			setMatrixTo(adjaGraph, NO_EDGE_VALUE); //Clear maxtix
			char tmpName[MAX_NAME_LENGTH];
			int x, y; float weight; 
			for (int i = 0; i < num && !error; ++i)
				if (!(openFile >> tmpName >> x >> y)) error = 1;
				else listv.addVertex(tmpName, x, y);
			if (!error)
				while (!openFile.eof())
				{
					if (!(openFile >> x >> y >> weight)) break;
					else adjaGraph[x][y] = weight;
				}
			isSaved = 1;
		}
		else error = 1;
		openFile.close();
	}
	if (error) 
	{
		listv.clear();
		setMatrixTo(adjaGraph, NO_EDGE_VALUE); //Clear maxtix
		MessageBox(hwnd, "LOI DOC FILE!!!", "Loi",  MB_APPLMODAL | MB_ICONERROR);
	}
}
void save()
{
	OPENFILENAME file;
	char fileName[MAX_PATH] = "\0";
	ZeroMemory(&file, sizeof(file));
	file.lStructSize = sizeof(file);
	file.lpstrFile = fileName;
	file.nMaxFile = sizeof(fileName);
	file.lpstrFilter = (FILE_FILTER);
	file.nFilterIndex = 1;
	file.hwndOwner = hwnd;
	file.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT;
	if (GetSaveFileName(&file) == 1)
	{
		if (!strstr(fileName, ".graph")) 
			strcat(fileName, ".graph"); // Add file name extension if it isn't exsit, but be aware !!! 
		std::ofstream saveFile(fileName);
		const int num = listv.num;
		saveFile << num << '\n';
		for (int i = 0; i < num; ++i)
			saveFile << listv.v[i]->name << ' ' << listv.v[i]->x << ' ' << listv.v[i]->y << '\n';
		saveFile << '\n'; // Endl between Vertexs and ListEdge
		for (int i = 0; i < num; ++i)
			for (int j = 0; j < num; ++j)
				if (adjaGraph[i][j] != NO_EDGE_VALUE)
					saveFile << i << ' ' << j << ' ' << adjaGraph[i][j] << '\n';
		saveFile.close();
		isSaved = 1;
	}
}
void quit()
{
	if (!isSaved && listv.num > 0)
	{
		int id = MessageBox(hwnd, "Ban co muon luu do thi lai khong?", "Save file",
								  MB_APPLMODAL | MB_ICONEXCLAMATION | MB_YESNOCANCEL);
		if (id == IDCANCEL) return;
		if (id == IDYES) return save();
	}
	closegraph();
	exit(EXIT_SUCCESS);
}

void drawEdge(int begin, int end, int color)
{
	const int &x1 = listv.v[begin]->x;
	const int &y1 = listv.v[begin]->y;
	const int &x2 = listv.v[end]->x;
	const int &y2 = listv.v[end]->y;
	if (adjaGraph[end][begin] == NO_EDGE_VALUE || begin < end)
		drawArrow(x1, y1, x2, y2, color, adjaGraph[begin][end]);
	else
		drawCurvedLine(x1, y1, x2, y2, color, adjaGraph[begin][end]);
}
void drawAllEdges()
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			if (adjaGraph[i][j] != NO_EDGE_VALUE)
				drawEdge(i, j, EDGE_COLOR);
}
int chooseVertex(int highLightColor, int skipReset)
{
	drawLimitZone();
	int x, y;
	int newPos(-1), oldPos(-1);
	while (1)
	{
		if (getKey() == KEY_ESC) break;
		newPos = listv.find(mousex(), mousey());
		if (newPos != oldPos)
		{
			if (newPos != -1 && newPos != skipReset) 
				listv.v[newPos]->show(highLightColor);
			if (oldPos != -1 && oldPos != skipReset)
				listv.v[oldPos]->show(VERTEX_COLOR);
			oldPos = newPos;
		}
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (!isInWorkingZone(x, y)) break;
			if (newPos != -1)
			{
				listv.v[newPos]->show(highLightColor);
				return newPos;
			}
		}
		delay(DELAY_VALUE);
	}
	return -1;
}
bool chooseStartVertex(int &start, const char *text1, const char *text2)
{
	setTextPrintStyle(TEXT_COLOR);
	printText(text1);
	start = chooseVertex(VERTEX_CHOOSING_COLOR);
	if (start == -1) return 0;
	setTextPrintStyle(TEXT_COLOR);
	printText(listv.v[start]->name);
	printTextWlb(text2);
	return 1;
	
}
bool chooseTwoVertices(int &start, int &stop)
{
	setTextPrintStyle(TEXT_COLOR);
	printText("Chon dinh xuat phat: ");
	start = chooseVertex(VERTEX_CHOOSING_COLOR);
	if (start == -1) return 0;
	setTextPrintStyle(TEXT_COLOR);
	printTextWl(listv.v[start]->name);
	listv.v[start]->show(VERTEX_CHOSE_COLOR);
	setTextPrintStyle(TEXT_COLOR);
	printText("Chon dinh ket thuc: ");
	stop = chooseVertex(VERTEX_CHOOSING_COLOR, start);
	if (stop == -1) return 0;
	setTextPrintStyle(TEXT_COLOR);
	printTextWl(listv.v[stop]->name);
	listv.v[stop]->show(VERTEX_CHOSE_COLOR);
	if (start == stop)
	{
		listv.v[stop]->show(VERTEX_COLOR);
		return 0;
	}
	return 1;
}
bool isEmptyGraph()
{
	if (listv.num == 0)
	{
		MessageBox(hwnd, "Do thi rong", "Loi", MB_APPLMODAL | MB_ICONERROR);
		return 1;
	}
	return 0;
}
void adjustSpeed(char key)
{
	if (key == KEY_LEFT)
		delayRunTime = (delayRunTime < MAX_SPEED) ? delayRunTime + 100 : MAX_SPEED;
	else if (key == KEY_RIGHT)
		delayRunTime = (delayRunTime > 100) ? delayRunTime - 100 : 0;
	showSpeed();
}
char getKey()
{
	if (kbhit())
	{
		char c = getch();
		switch (c)
		{
			case KEY_ESC:
				return KEY_ESC;
			case ARROW_KEY:
				c = getch();
				adjustSpeed(c);
				return c;
			case KEY_Q:
				return KEY_Q;
			case KEY_LQ:
				return KEY_Q;
			default:
				return KEY_NULL;
		}
	}
	return KEY_NULL;
}
void showResultStack(stack &s)
{
	int v, u = s.pop();
	setTextPrintStyle(TEXT_COLOR);
	printText(listv.v[u]->name);
	listv.v[u]->show(VERTEX_CHOSE_COLOR);
	while (!s.isEmpty())
	{
		v = s.pop();
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText("->");
		printText(listv.v[v]->name);
		drawEdge(u, v, EDGE_VISTED_COLOR);
		listv.v[v]->show(VERTEX_VISTED_COLOR);
		u = v;
		if (getKey() == KEY_ESC) return;
		delay(delayRunTime);
	}
}

void setTextPrintStyle(int color)
{
//	setusercharsize(9, 10, 9, 10);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
	setbkcolor(BACKGROUND_COLOR);
	setcolor(color);
	settextjustify(LEFT_TEXT, TOP_TEXT);
}
bool getInputWeight(float &res)
{
	char str[10];
	getInputChar(str, 10, inputFloat);
	if (!isFloat(str)) return 0;
	res = roundf(toFloat(str) * 100) / 100;
	if (res > MAX_WEIGHT || res < MIN_WEIGHT)
	{
		char msg[70]; char w[10];
		strcpy(msg, "Trong so khong cho phep.\nTrong so >= ");
		convertToChar(MIN_WEIGHT, w);
		strcat(msg, w);
		strcat(msg, " & Trong so <= ");
		convertToChar(MAX_WEIGHT, w);
		strcat(msg, w);
		MessageBox(hwnd, msg, "Loi", MB_APPLMODAL | MB_ICONERROR);
		return 0;
	}
	return 1;
}
bool getInputChar(char *str, int max, bool (*checkKey)(char key))
{
	setTextPrintStyle(BLUE);
	int i = 0; str[0] = '\0';
	char key[2] = {'\0', '\0'};
	while (i < max)
	{
		if (kbhit())
		{
			key[0] = getch();
			if (key[0] == KEY_ESC || key[0] == KEY_ENTER) break;
			if (key[0] == KEY_BACKSPACE && i > 0) {--i; key[0] = str[i]; deleteText(key); str[i] = '\0';}
			else if (checkKey(key[0])) {strcat(str, key); ++i; printText(key);}
		}
		if (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
		delay(DELAY_VALUE);
	}
	return (i > 0);
}
void deleteText(const char* str)
{
	if (xCursor <= xCURSOR) return;
	const int currentColor = getcolor();
	setTextPrintStyle(BACKGROUND_COLOR);
	const int tw = textwidth(str);
	xCursor -= tw;
	printText(str);
	xCursor -= tw;
	setTextPrintStyle(currentColor);
}
void printText(const char *str)
{
	int const tw = textwidth(str);
	if (xCursor + tw >= tRIGHT)
	{
		xCursor = xCURSOR;
		yCursor += TEXTHIGHT;
	}
	if (yCursor > tBOTTOM - TEXTHIGHT)
	{
		drawTextZone();
		xCursor = xCURSOR;
		yCursor = yCURSOR;
		setTextPrintStyle(TEXT_COLOR);
	}
	outtextxy(xCursor, yCursor, str);
	xCursor += tw;
}
void printText(float value)
{
	char str[MAX_INPUT];
	convertToChar(value, str);
	printText(str);
}
template <typename Type>
void printTextWl(Type s)
{
	printText(s);
	xCursor = xCURSOR;
	yCursor += TEXTHIGHT;
}
template <typename Type>
void printTextWlb(Type s)
{
	xCursor = xCURSOR;
	yCursor += TEXTHIGHT;
	printText(s);
}
void addVertex()
{
	drawLimitZone();
	if (listv.num == MAX_VERTEX)
	{
		char msg[45], num[3];
		strcpy(msg, "Qua so luong dinh cho phep MAX_VERTEX = ");
		convertToChar(MAX_VERTEX, num);
		strcat(msg, num);
		MessageBox(hwnd, msg, "Loi", MB_APPLMODAL | MB_ICONERROR);
	}
	int x, y;
	setTextPrintStyle(TEXT_COLOR);
	printText("Click chuot de them dinh.");
	while (listv.num < MAX_VERTEX)
	{
		if (getKey() == KEY_ESC) break;
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (listv.find(x, y) != -1)
			{
				MessageBox(hwnd, "Trung dinh da co\nVui long chon lai.", "Loi",
							MB_APPLMODAL | MB_ICONERROR);
				continue;
			}
			if (isInLimitZone(x, y))
			{
				listv.addVertex(x, y);
				drawMatrixZone();
				isSaved = 0;
			}
			else break;
		}
		delay(DELAY_VALUE);
	}
}
void addEdges()
{
	if (isEmptyGraph()) return;
	int begin, end, oldEnd = -1;
	float weight;
	setTextPrintStyle(TEXT_COLOR);
	printText("Noi hai dinh de them/xoa cung.");
	while (1)
	{
		begin = chooseVertex(VERTEX_CHOOSING_COLOR);
		if (begin == -1) break;
		int x = listv.v[begin]->x;
		int y = listv.v[begin]->y;
		if (ismouseclick(WM_LBUTTONUP)) clearmouseclick(WM_LBUTTONUP);
		while (!ismouseclick(WM_LBUTTONUP))
		{
			setactivepage(1 - getactivepage());
			initScreen();
			drawLimitZone();
			drawAllEdges();
			listv.showAll();
			listv.v[begin]->show(VERTEX_CHOSE_COLOR);
			menuButton[ADD_EDGE_MENU].showChoseButton();
			showButtonIcon(menuButton, ADD_EDGE_MENU);
			end = listv.find(mousex(), mousey());
			drawArrow(x, y, mousex(), mousey(), EDGE_HIGHTLIGHT_COLOR, 0);
			setvisualpage(getactivepage());
			if (oldEnd != -1 && oldEnd != end && oldEnd != begin)
				listv.v[oldEnd]->show(VERTEX_COLOR);
			if (end != begin && end != -1 && end != oldEnd)
				listv.v[end]->show(VERTEX_CHOOSING_COLOR);
			oldEnd = end;
			if (!isInWorkingZone(mousex(), mousey())) break;
			delay(DELAY_VALUE);
		}
		if (end == -1 || end == begin)
		{
			refreshGraph(ADD_EDGE_MENU);
			listv.v[begin]->show(VERTEX_COLOR);
			continue;
		}
		listv.v[end]->show(VERTEX_CHOSE_COLOR);
		setvisualpage(getactivepage());
		adjaGraph[begin][end] = DEFAULT_WEIGHT;
		refreshGraph(ADD_EDGE_MENU);
		drawEdge(begin, end, EDGE_HIGHTLIGHT_COLOR);
		setTextPrintStyle(TEXT_COLOR);
		printText("Nhap trong so (xoa cung nhap '-') cung ");
		printText(listv.v[begin]->name);
		printText("->");
		printText(listv.v[end]->name);
		printText(": ");
		if (getInputWeight(weight)) adjaGraph[begin][end] = weight;
		else adjaGraph[begin][end] = NO_EDGE_VALUE;
		isSaved = 0;
		refreshGraph(ADD_EDGE_MENU);
		listv.v[begin]->show(VERTEX_COLOR);
		listv.v[end]->show(VERTEX_COLOR);
	}
}
void renameVertex()
{
	if (isEmptyGraph()) return;
	int choose;
	while (1)
	{
		if (chooseStartVertex(choose, "Chon dinh can doi ten: ", "Nhap ten moi cho dinh "))
		{
			printText(listv.v[choose]->name);
			printText(": ");
			listv.v[choose]->show(VERTEX_CHOSE_COLOR);
			char name[MAX_NAME_LENGTH];
			if (getInputChar(name, MAX_NAME_LENGTH - 1, inputAscii) && !listv.isExist(name))
			{
				listv.updateCurrentName(name);
				listv.v[choose]->clearName();
				strcpy(listv.v[choose]->name, name);
				drawMatrixZone();
				isSaved = 0;
			}
			else MessageBox(hwnd, "Trung ten hoac nhap sai", "Loi", MB_APPLMODAL | MB_ICONERROR);
			listv.v[choose]->show(VERTEX_COLOR);
			printTextWl("");
		} else break;
	}
}
void deleteVertex()
{
	if (isEmptyGraph()) return;
	while (listv.num > 0)
	{
		setTextPrintStyle(TEXT_COLOR);
		printText("Chon dinh can xoa: ");
		int choose = chooseVertex(VERTEX_DELETE_COLOR);
		if (choose == -1) break;
		setTextPrintStyle(VERTEX_DELETE_COLOR);
		printText(listv.v[choose]->name);
		removeVertex(choose);
		listv.deleteVertex(choose); // --num is in here
		refreshGraph(DELETEVE_MENU);
		isSaved = 0;
		if (listv.num == 0)
			listv.clear();
	}
}
void moveVertex()
{
	if (isEmptyGraph()) return;
	int x, y;
	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Dung thao tac keo/tha dinh de di chuyen tung dinh");
	printText("hoac Ctr + keo/tha de di chuyen toan bo do thi.");
	while (1)
	{
		int choose = chooseVertex(VERTEX_CHOOSING_COLOR);
		if  (choose == -1) break;
		if (ismouseclick(WM_LBUTTONUP)) clearmouseclick(WM_LBUTTONUP);
		isSaved = 0;
		listv.v[choose]->show(VERTEX_CHOSE_COLOR);
		while (!ismouseclick(WM_LBUTTONUP))
		{
			if (ismouseclick(WM_MOUSEMOVE))
			{
				getmouseclick(WM_MOUSEMOVE, x, y);
				if (!isInLimitZone(x, y)) continue;
				if (GetKeyState(VK_CONTROL) < 0) // Crt + move all vertices
				{
					int dx = x - listv.v[choose]->x;
					int dy = y - listv.v[choose]->y;
					for (int i = 0; i < listv.num; ++i)
					{
						listv.v[i]->x += dx;
						listv.v[i]->y += dy;
						if (!isInLimitZone(listv.v[i]->x, listv.v[i]->y))
						{
							for (int j = i; j >= 0; --j)
							{
								listv.v[j]->x -= dx;
								listv.v[j]->y -= dy;
							}
							break;
						}
					}
				} else listv.v[choose]->setCoordinate(x, y); // Move single vertex
				setactivepage(1 - getactivepage());
				initScreen();
				drawLimitZone();
				drawAllEdges();
				listv.showAll();
				menuButton[MOVEVE_MENU].showChoseButton();
				showButtonIcon(menuButton, MOVEVE_MENU);
				setvisualpage(getactivepage());
			}
			delay(DELAY_VALUE);
		}
		listv.v[choose]->show(VERTEX_COLOR);
		setvisualpage(getactivepage());
	}
}
void cleanGraph()
{
	if (isEmptyGraph()) return;
	if (MessageBox(hwnd, "Ban co chac khong?", "Xoa do thi",
		MB_APPLMODAL| MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		listv.clear();
		setMatrixTo(adjaGraph, NO_EDGE_VALUE);
		refreshGraph(CLEAN_GRAPH_MENU);
		isSaved = 1;
	}
}
void help()
{
	MessageBox(hwnd, "Chuong trinh demo Do thi co huong co trong so.\n"
					"Su dung:\n"
					"Phim <ESC> : Huy chuc nang.\n"
					"Phim <Q>/<q> : Thoat chuong trinh.\n"
					"Phim <LEFT>/<RIGHT> : Chinh toc do giam/tang.\n"
					"Nhóm: TH-TrueMilk\n"
					"Tac gia:\n"
					"Nguyen Dat Minh 46.01.104.100\n"
					"Lam Chan Huy 46.01.104.069\n"
					"Le Dinh Anh Tuan 46.01.104.209\n",
				 	"Help", MB_APPLMODAL | MB_ICONINFORMATION);
}
int findButton(int x, int y)
{
	for (int i = 0; i < NUM_OF_MENU; ++i)
		if (menuButton[i].isButtonClick(x, y))
			return i;
	return -1;
}
void backToMenu()
{
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Nhan phim bat ky hoac click chuot de tiep tuc.");
	if (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
	fflush(stdin);
	while (1)
	{
		if (kbhit()) break;
		if (ismouseclick(WM_LBUTTONDOWN)) break;
		delay(DELAY_VALUE);
	}
	if (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
	fflush(stdin);
}
void switchMenuItem(int chose)
{
	switch (chose)
	{
		case FLOYD_MENU: 			return Floyd();
		case KRUSKAL_MENU:			return Kruskal();	
		case OPEN_MENU: 			return open();
		case SAVE_MENU:				return save();
		case QUIT_MENU: 			return quit();
		case ADD_VERTEX_MENU:	 	return addVertex();
		case ADD_EDGE_MENU: 		return addEdges();
		case RENAME_VERTEX_MENU: 	return renameVertex();
		case DELETEVE_MENU: 		return deleteVertex();
		case MOVEVE_MENU: 			return moveVertex();
		case CLEAN_GRAPH_MENU: 		return cleanGraph();
		case HELP_MENU: 			return help();
		default: return;
	}
}
void refreshScreen()
{
	setactivepage(1 - getactivepage());
	initScreen();
	drawAllEdges();
	listv.showAll(VERTEX_COLOR);
	setvisualpage(getactivepage());
}
void refreshGraph(int mPos)
{
	setactivepage(1 - getactivepage());
	drawWorkingZone();
	drawMatrixZone();
	drawTextZone();
	showAllButtons();
	drawAllEdges();
	listv.showAll();
	menuButton[mPos].showChoseButton();
	showButtonIcon(menuButton, mPos);
	setvisualpage(getactivepage());
}
inline void showChoseButton(int pos)
{
	if (pos >= ADD_VERTEX_MENU) refreshScreen();
	menuButton[pos].showChoseButton();
	showButtonIcon(menuButton, pos);
}
inline void showHightLightButton(int pos)
{
	menuButton[pos].showHightLightButton();
	if (pos >= ADD_VERTEX_MENU) menuButton[pos].showButtonHint();
	showButtonIcon(menuButton, pos);
}
inline void showNormalButton(int pos)
{
	if (pos >= ADD_VERTEX_MENU) refreshScreen();
	menuButton[pos].showNormalButton();
	showButtonIcon(menuButton, pos);
}
inline void update(int &oldPos, int &newPos, int x, int y)
{
	newPos = findButton(x, y);
	if (newPos != oldPos)
	{
		if (oldPos != -1) showNormalButton(oldPos);
		if (newPos != -1) showHightLightButton(newPos);
		oldPos = newPos;
	}
}
void menu()
{
	int x, y;
	int newPos(-1), oldPos(-1);
	while (1)
	{
		if (getKey() == KEY_Q) quit();
		if (ismouseclick(WM_MOUSEMOVE))
		{
			getmouseclick(WM_MOUSEMOVE, x, y);
			update(oldPos, newPos, x, y);
		}
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			clearmouseclick(WM_LBUTTONDOWN);
			if (newPos != -1)
			{
				showChoseButton(newPos);
				switchMenuItem(newPos);
			}
			oldPos = -1;
			refreshScreen();
			update(oldPos, newPos, mousex(), mousey());
		}
		delay(DELAY_VALUE);
	}
}
