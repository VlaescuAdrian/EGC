#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}


Mesh* Object2D::CreateBackround(std::string name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(0,0,-2), color),
		VertexFormat(corner + glm::vec3(width, 0, -2), color),
		VertexFormat(corner + glm::vec3(width, height, -2), color),
		VertexFormat(corner + glm::vec3(0, height, -2), color)
	};

	Mesh* backround = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 0, 2 };


	backround->InitFromData(vertices, indices);
	return backround;
}
Mesh* Object2D::CreatePrincipalBird(std::string name, glm::vec3 corner, glm::vec3 red, glm::vec3 black, glm::vec3 white, glm::vec3 orange, glm::vec3 yellow)
{
	float h = 4;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner,black), //0
		VertexFormat(corner + glm::vec3(h,0,0),black), //1
		VertexFormat(corner + glm::vec3(h,h,0),black), //2 
		VertexFormat(corner + glm::vec3(0,h,0),black), //3

		VertexFormat(corner + glm::vec3(2*h,0,0),black), //4
		VertexFormat(corner + glm::vec3(2*h,h,0),black), //5 
		VertexFormat(corner + glm::vec3(3 * h,0,0),black), //6
		VertexFormat(corner + glm::vec3(3 * h,h,0),black), //7 


		VertexFormat(corner + glm::vec3(0,h,0),orange), //8
		VertexFormat(corner + glm::vec3(h,h,0),orange), //9
		VertexFormat(corner + glm::vec3(h,2*h,0),orange), //10
		VertexFormat(corner + glm::vec3(0,2*h,0),orange), //11

		VertexFormat(corner + glm::vec3(2 * h,h,0),orange), //12
		VertexFormat(corner + glm::vec3(2 * h,2*h,0),orange), //13
		VertexFormat(corner + glm::vec3(3 * h,h,0),orange), //14
		VertexFormat(corner + glm::vec3(3 * h,2* h,0),orange), //15 

		VertexFormat(corner + glm::vec3(2 * h,2*h,0),black), //16
		VertexFormat(corner + glm::vec3(3 * h,2 * h,0),black), //17
		VertexFormat(corner + glm::vec3(3 * h,3* h,0),black), //18
		VertexFormat(corner + glm::vec3(2 * h,3 * h,0),black), //19

		VertexFormat(corner + glm::vec3(3*h,h,0),black), //20
		VertexFormat(corner + glm::vec3(4*h,h,0),black), //21
		VertexFormat(corner + glm::vec3(4*h,2 * h,0),black), //22
		VertexFormat(corner + glm::vec3(3*h,2 * h,0),black), //23

		VertexFormat(corner + glm::vec3(5 * h,h,0),black), //24
		VertexFormat(corner + glm::vec3(5 * h,2 * h,0),black), //25
		VertexFormat(corner + glm::vec3(6 * h,h,0),black), //26
		VertexFormat(corner + glm::vec3(6 * h,2 * h,0),black), //27 

		VertexFormat(corner + glm::vec3(3 * h,h,0),red), //28
		VertexFormat(corner + glm::vec3(4 * h,h,0),red), //29
		VertexFormat(corner + glm::vec3(4 * h,3 * h,0),red), //30
		VertexFormat(corner + glm::vec3(3 * h,3 * h,0),red), //31

		VertexFormat(corner + glm::vec3(5 * h,h,0),red), //32
		VertexFormat(corner + glm::vec3(5 * h,3 * h,0),red), //33
		VertexFormat(corner + glm::vec3(6 * h,h,0),red), //34
		VertexFormat(corner + glm::vec3(6 * h,3 * h,0),red), //35

		VertexFormat(corner + glm::vec3(3 * h,h,0),black), //36
		VertexFormat(corner + glm::vec3(4 * h,h,0),black), //37
		VertexFormat(corner + glm::vec3(4 * h,4 * h,0),black), //38
		VertexFormat(corner + glm::vec3(3 * h,4 * h,0),black), //39

		VertexFormat(corner + glm::vec3(5 * h,h,0),black), //40
		VertexFormat(corner + glm::vec3(5 * h,4 * h,0),black), //41
		VertexFormat(corner + glm::vec3(6 * h,h,0),black), //42
		VertexFormat(corner + glm::vec3(6 * h,4 * h,0),black), //43

		VertexFormat(corner + glm::vec3(7 * h,2 * h,0),black), //44
		VertexFormat(corner + glm::vec3(7 * h,3* h,0),black), //45
		VertexFormat(corner + glm::vec3(7 * h,4 * h,0),black), //46

		VertexFormat(corner + glm::vec3(2 * h,3 * h,0),red), //47
		VertexFormat(corner + glm::vec3(3 * h,4 * h,0),red), //48
		VertexFormat(corner + glm::vec3(2 * h,4 * h,0),red), //49

		VertexFormat(corner + glm::vec3(4 * h,4*h,0),red), //50
		VertexFormat(corner + glm::vec3(4 * h,5 * h,0),red), //51
		VertexFormat(corner + glm::vec3(3 * h,5 * h,0),red), //52

		VertexFormat(corner + glm::vec3(5 * h,4*h,0),red), //53
		VertexFormat(corner + glm::vec3(5 * h,5 * h,0),red), //54
		VertexFormat(corner + glm::vec3(6 * h,4*h,0),red), //55
		VertexFormat(corner + glm::vec3(6 * h,5 * h,0),red), //56
		VertexFormat(corner + glm::vec3(7 * h,4*h,0),red), //57
		VertexFormat(corner + glm::vec3(7 * h,5 * h,0),red), //58

		VertexFormat(corner + glm::vec3(7 * h,4 * h,0),black), //59
		VertexFormat(corner + glm::vec3(8 * h,4 * h,0),black), //60
		VertexFormat(corner + glm::vec3(8 * h,5 * h,0),black), //61
		VertexFormat(corner + glm::vec3(7 * h,5 * h,0),black), //62

		VertexFormat(corner + glm::vec3(8 * h,4 * h,0),red), //63
		VertexFormat(corner + glm::vec3(8 * h,6 * h,0),red), //64
		VertexFormat(corner + glm::vec3(10 * h,5 * h,0),red), //65

		VertexFormat(corner + glm::vec3(8 * h,6 * h,0),black), //66
		VertexFormat(corner + glm::vec3(7 * h,6 * h,0),black), //67

		VertexFormat(corner + glm::vec3(3 * h,5 * h,0),black), //68
		VertexFormat(corner + glm::vec3(4 * h,5 * h,0),black), //69
		VertexFormat(corner + glm::vec3(4 * h,6 * h,0),black), //70
		VertexFormat(corner + glm::vec3(3 * h,6 * h,0),black), //71
		VertexFormat(corner + glm::vec3(5 * h,5 * h,0),black), //72
		VertexFormat(corner + glm::vec3(5 * h,6 * h,0),black), //73
		VertexFormat(corner + glm::vec3(6 * h,5 * h,0),black), //74
		VertexFormat(corner + glm::vec3(6 * h,6 * h,0),black), //75

		VertexFormat(corner + glm::vec3(3 * h,6 * h,0),white), //76
		VertexFormat(corner + glm::vec3(4 * h,6 * h,0),white), //77
		VertexFormat(corner + glm::vec3(4 * h,7 * h,0),white), //78
		VertexFormat(corner + glm::vec3(3 * h,7 * h,0), white), //79
		VertexFormat(corner + glm::vec3(5 * h,6 * h,0), white), //80
		VertexFormat(corner + glm::vec3(5 * h,7 * h,0), white), //81
		VertexFormat(corner + glm::vec3(6 * h,6 * h,0), white), //82
		VertexFormat(corner + glm::vec3(6 * h,7 * h,0), white), //83

		VertexFormat(corner + glm::vec3(6 * h,6 * h,0), black), //84
		VertexFormat(corner + glm::vec3(7 * h,7 * h,0), black), //85
		VertexFormat(corner + glm::vec3(6 * h,7 * h,0), black), //86
		VertexFormat(corner + glm::vec3(7 * h,8 * h,0), black), //87
		VertexFormat(corner + glm::vec3(6 * h,8 * h,0), black), //88
		VertexFormat(corner + glm::vec3(7 * h,9 * h,0), black), //89
		VertexFormat(corner + glm::vec3(6 * h,9 * h,0), black), //90

		VertexFormat(corner + glm::vec3(5 * h,9 * h,0), black), //91
		VertexFormat(corner + glm::vec3(6 * h,10 * h,0), black), //92
		VertexFormat(corner + glm::vec3(5 * h,10 * h,0), black), //93

		VertexFormat(corner + glm::vec3(4 * h, 10 * h, 0), black), //94
		VertexFormat(corner + glm::vec3(5 * h, 11 * h, 0), black), //95
		VertexFormat(corner + glm::vec3(4 * h, 11 * h, 0), black), //96



		VertexFormat(corner + glm::vec3(4 * h,9 * h,0),white), //97
		VertexFormat(corner + glm::vec3(5 * h,9 * h,0),white), //98
		VertexFormat(corner + glm::vec3(5 * h,10 * h,0),white), //99
		VertexFormat(corner + glm::vec3(4 * h,10 * h,0), white), //100
		VertexFormat(corner + glm::vec3(3 * h,9 * h,0), white), //101
		VertexFormat(corner + glm::vec3(4 * h,9 * h,0), white), //102
		VertexFormat(corner + glm::vec3(4 * h,10 * h,0), white), //103
		VertexFormat(corner + glm::vec3(3 * h,10 * h,0), white), //104
		VertexFormat(corner + glm::vec3(3 * h,8 * h,0),white), //105
		VertexFormat(corner + glm::vec3(4 * h,8 * h,0),white), //106
		VertexFormat(corner + glm::vec3(3 * h,7 * h,0),white), //107
		VertexFormat(corner + glm::vec3(4 * h,7 * h,0), white), //108
		VertexFormat(corner + glm::vec3(5 * h,7 * h,0), white), //109
		VertexFormat(corner + glm::vec3(5 * h,8 * h,0), white), //110
		VertexFormat(corner + glm::vec3(6 * h,7 * h,0), white), //111
		VertexFormat(corner + glm::vec3(6 * h,8 * h,0), white), //112
		VertexFormat(corner + glm::vec3(6 * h,9 * h,0), white), //113
		VertexFormat(corner + glm::vec3(5 * h,9 * h,0), white), //114

		VertexFormat(corner + glm::vec3(4 * h, 8 * h, 0), black), //115
		VertexFormat(corner + glm::vec3(5 * h, 8 * h, 0), black), //116
		VertexFormat(corner + glm::vec3(4 * h, 9 * h, 0), black), //117

		VertexFormat(corner + glm::vec3(2 * h, 9 * h, 0), black), //118
		VertexFormat(corner + glm::vec3(3 * h, 9 * h, 0), black), //119
		VertexFormat(corner + glm::vec3(3 * h, 10 * h, 0), black), //120
		VertexFormat(corner + glm::vec3(2 * h, 10 * h, 0), black), //121

		VertexFormat(corner + glm::vec3(2 * h, 8 * h, 0), white), //122
		VertexFormat(corner + glm::vec3(2 * h, 9 * h, 0), white), //123
		VertexFormat(corner + glm::vec3(2 * h, 7* h, 0), white), //124

		VertexFormat(corner + glm::vec3(2 * h, 6 * h, 0), black), //125
		VertexFormat(corner + glm::vec3(3 * h, 7 * h, 0), black), //126
		VertexFormat(corner + glm::vec3(2 * h, 7 * h, 0), black), //127

		VertexFormat(corner + glm::vec3(2 * h, 5* h, 0), yellow), //128
		VertexFormat(corner + glm::vec3(3 * h, 5 * h, 0), yellow), //129
		VertexFormat(corner + glm::vec3(3 * h, 6 * h, 0), yellow), //130
		VertexFormat(corner + glm::vec3(2 * h, 6 * h, 0), yellow), //131

		VertexFormat(corner + glm::vec3(2 * h, 4 * h, 0), black), //132
		VertexFormat(corner + glm::vec3(3 * h, 4 * h, 0), black), //133
		VertexFormat(corner + glm::vec3(2 * h, 5 * h, 0), black), //134

		VertexFormat(corner + glm::vec3(1 * h, 7 * h, 0), black), //135
		VertexFormat(corner + glm::vec3(2 * h, 8 * h, 0), black), //136
		VertexFormat(corner + glm::vec3(1 * h, 8 * h, 0), black), //137
		VertexFormat(corner + glm::vec3(1 * h, 9 * h, 0), black), //138

		VertexFormat(corner + glm::vec3(1 * h, 5* h, 0), yellow), //139
		VertexFormat(corner + glm::vec3(1 * h, 6 * h, 0), yellow), //140
		VertexFormat(corner + glm::vec3(2 * h, 7 * h, 0), yellow), //141
		VertexFormat(corner + glm::vec3(1 * h, 7 * h, 0), yellow), //142
		VertexFormat(corner + glm::vec3(0 * h, 5* h, 0), yellow), //143
		VertexFormat(corner + glm::vec3(0 * h, 6 * h, 0), yellow), //144
		VertexFormat(corner + glm::vec3(0 * h, 7 * h, 0), yellow), //145
		VertexFormat(corner + glm::vec3(1 * h, 8 * h, 0), yellow), //146
		VertexFormat(corner + glm::vec3(0 * h, 8* h, 0), yellow), //147
		VertexFormat(corner + glm::vec3(1 * h, 9 * h, 0), yellow), //148
		VertexFormat(corner + glm::vec3(0 * h, 9 * h, 0), yellow), //149
		VertexFormat(corner + glm::vec3(-1 * h, 9 * h, 0), yellow), //150
		VertexFormat(corner + glm::vec3(-1 * h, 8 * h, 0), yellow), //151
		VertexFormat(corner + glm::vec3(-1 * h, 7 * h, 0), yellow), //152

		VertexFormat(corner + glm::vec3(-1 * h, 5 * h, 0), black), //153
		VertexFormat(corner + glm::vec3(0 * h, 5 * h, 0), black), //154
		VertexFormat(corner + glm::vec3(0 * h, 6 * h, 0), black), //155
		VertexFormat(corner + glm::vec3(-1 * h, 6 * h, 0), black), //156
		VertexFormat(corner + glm::vec3(0 * h, 7 * h, 0), black), //157
		VertexFormat(corner + glm::vec3(-1 * h, 7 * h, 0), black), //158

		VertexFormat(corner + glm::vec3(-1 * h, 9 * h, 0), white), //159
		VertexFormat(corner + glm::vec3(-1 * h, 9 * h, 0), white), //160
		VertexFormat(corner + glm::vec3(0 * h, 10 * h, 0), white), //161
		VertexFormat(corner + glm::vec3(-1 * h, 10 * h, 0), white), //162
		VertexFormat(corner + glm::vec3(1 * h, 9 * h, 0), white), //163
		VertexFormat(corner + glm::vec3(1 * h, 10 * h, 0), white), //164
		VertexFormat(corner + glm::vec3(2 * h, 10 * h, 0), white), //165



		VertexFormat(corner + glm::vec3(-2 * h, 9 * h, 0), black), //166
		VertexFormat(corner + glm::vec3(-1 * h, 9 * h, 0), black), //167
		VertexFormat(corner + glm::vec3(-1 * h, 10 * h, 0), black), //168
		VertexFormat(corner + glm::vec3(-2 * h, 10 * h, 0), black), //169
		VertexFormat(corner + glm::vec3(-1 * h, 11 * h, 0), black), //170
		VertexFormat(corner + glm::vec3(-2 * h, 11 * h, 0), black), //171
		VertexFormat(corner + glm::vec3(0 * h, 10 * h, 0), black), //172
		VertexFormat(corner + glm::vec3(0 * h,11 * h, 0), black), //173
		VertexFormat(corner + glm::vec3(1 * h, 10 * h, 0), black), //174
		VertexFormat(corner + glm::vec3(1 * h, 11 * h, 0), black), //175
		VertexFormat(corner + glm::vec3(2 * h, 10 * h, 0), black), //176
		VertexFormat(corner + glm::vec3(2 * h, 11 * h, 0), black), //177
		VertexFormat(corner + glm::vec3(3 * h, 10 * h, 0), black), //178
		VertexFormat(corner + glm::vec3(3 * h, 11 * h, 0), black), //179

		VertexFormat(corner + glm::vec3(-2 * h, 8 * h, 0), white), //180
		VertexFormat(corner + glm::vec3(-1 * h, 8 * h, 0), white), //181
		VertexFormat(corner + glm::vec3(-2 * h, 9 * h, 0), white), //182

		VertexFormat(corner + glm::vec3(-2 * h, 7 * h, 0), black), //183
		VertexFormat(corner + glm::vec3(-1 * h, 8 * h, 0), black), //184
		VertexFormat(corner + glm::vec3(-2 * h, 8 * h, 0), black), //185

		VertexFormat(corner + glm::vec3(-2 * h, 6 * h, 0), white), //186
		VertexFormat(corner + glm::vec3(-1 * h, 6 * h, 0), white), //187
		VertexFormat(corner + glm::vec3(-1 * h, 7 * h, 0), white), //188
		VertexFormat(corner + glm::vec3(-2 * h, 7 * h, 0), white), //189

		VertexFormat(corner + glm::vec3(-2 * h, 5 * h, 0), yellow), //190
		VertexFormat(corner + glm::vec3(-1 * h, 5 * h, 0), yellow), //191
		VertexFormat(corner + glm::vec3(-1 * h, 6 * h, 0), yellow), //192
		VertexFormat(corner + glm::vec3(-2 * h, 6 * h, 0), yellow), //193
		VertexFormat(corner + glm::vec3(-1 * h, 4 * h, 0), yellow), //194
		VertexFormat(corner + glm::vec3(-0 * h, 4 * h, 0), yellow), //195
		VertexFormat(corner + glm::vec3(1 * h, 4 * h, 0), yellow), //196
		VertexFormat(corner + glm::vec3(2 * h, 4 * h, 0), yellow), //197

		VertexFormat(corner + glm::vec3(1 * h, 3 * h, 0), black), //198
		VertexFormat(corner + glm::vec3(1 * h, 4 * h, 0), black), //199

		VertexFormat(corner + glm::vec3(-2 * h, 4 * h, 0), black), //200
		VertexFormat(corner + glm::vec3(-1 * h, 4 * h, 0), black), //201
		VertexFormat(corner + glm::vec3(-2 * h, 5 * h, 0), black), //202

		VertexFormat(corner + glm::vec3(-2 * h, 0 * h, 0), black), //203
		VertexFormat(corner + glm::vec3(-1 * h, 0 * h, 0), black), //204
		VertexFormat(corner + glm::vec3(-1 * h, 1 * h, 0), black), //205
		VertexFormat(corner + glm::vec3(-2 * h, 1 * h, 0), black), //206

		VertexFormat(corner + glm::vec3(-2 * h, 1* h, 0), orange), //207
		VertexFormat(corner + glm::vec3(-1 * h, 1 * h, 0), orange), //208
		VertexFormat(corner + glm::vec3(-1 * h, 2 * h, 0), orange), //209
		VertexFormat(corner + glm::vec3(-2 * h, 2 * h, 0), orange), //210
		VertexFormat(corner + glm::vec3(-1 * h, 3 * h, 0), orange), //211
		VertexFormat(corner + glm::vec3(-2 * h, 3 * h, 0), orange), //212
		VertexFormat(corner + glm::vec3(0 * h, 3 * h, 0), orange), //213
		VertexFormat(corner + glm::vec3(1 * h, 3 * h, 0), orange), //214
		VertexFormat(corner + glm::vec3(2 * h, 3 * h, 0), orange), //215
		VertexFormat(corner + glm::vec3(-2 * h, 4 * h, 0), orange), //216
		VertexFormat(corner + glm::vec3(-1 * h, 4 * h, 0), orange), //217
		VertexFormat(corner + glm::vec3(0 * h, 4 * h, 0), orange), //218
		VertexFormat(corner + glm::vec3(1 * h, 4 * h, 0), orange), //219

		VertexFormat(corner + glm::vec3(-3 * h, 9 * h, 0), black), //220
		VertexFormat(corner + glm::vec3(-3 * h, 10 * h, 0), black), //221
		VertexFormat(corner + glm::vec3(-4 * h, 8 * h, 0), black), //222
		VertexFormat(corner + glm::vec3(-3 * h, 8 * h, 0), black), //223
		VertexFormat(corner + glm::vec3(-4 * h, 9 * h, 0), black), //224
		VertexFormat(corner + glm::vec3(-4 * h, 7 * h, 0), black), //225
		VertexFormat(corner + glm::vec3(-3 * h, 7 * h, 0), black), //226

		VertexFormat(corner + glm::vec3(-3 * h, 8* h, 0), white), //227
		VertexFormat(corner + glm::vec3(-3 * h, 9 * h, 0), white), //228


		VertexFormat(corner + glm::vec3(-4* h, 4 * h, 0), white), //229
		VertexFormat(corner + glm::vec3(-3* h, 4 * h, 0), white), //230
		VertexFormat(corner + glm::vec3(-3 * h, 5 * h, 0), white), //231
		VertexFormat(corner + glm::vec3(-4 * h, 5 * h, 0), white), //232
		VertexFormat(corner + glm::vec3(-2 * h, 4 * h, 0), white), //233
		VertexFormat(corner + glm::vec3(-2 * h, 5 * h, 0), white), //234
		VertexFormat(corner + glm::vec3(-4 * h, 6 * h, 0), white), //235
		VertexFormat(corner + glm::vec3(-3 * h, 6 * h, 0), white), //236
		VertexFormat(corner + glm::vec3(-4 * h, 7 * h, 0), white), //237
		VertexFormat(corner + glm::vec3(-3 * h, 7* h, 0), white), //238

		VertexFormat(corner + glm::vec3(-3* h, 1 * h, 0), black), //239
		VertexFormat(corner + glm::vec3(-2 * h, 2 * h, 0), black), //240
		VertexFormat(corner + glm::vec3(-3 * h, 2 * h, 0), black), //241
		VertexFormat(corner + glm::vec3(-4 * h, 2 * h, 0), black), //242
		VertexFormat(corner + glm::vec3(-3 * h, 3 * h, 0), black), //243
		VertexFormat(corner + glm::vec3(-4 * h, 3 * h, 0), black), //244
		VertexFormat(corner + glm::vec3(-3 * h, 4 * h, 0), black), //245
		VertexFormat(corner + glm::vec3(-4 * h, 4 * h, 0), black), //246
		VertexFormat(corner + glm::vec3(-2 * h, 3* h, 0), black), //247

		VertexFormat(corner + glm::vec3(-3 * h, 2 * h, 0), orange),//248
		VertexFormat(corner + glm::vec3(-3 * h, 3* h, 0), orange),//249


		VertexFormat(corner + glm::vec3(-5* h, 3 * h, 0), black), //250
		VertexFormat(corner + glm::vec3(-5 * h, 4 * h, 0), black), //251
		VertexFormat(corner + glm::vec3(-5 * h, 5 * h, 0), black), //252
		VertexFormat(corner + glm::vec3(-4 * h, 5 * h, 0), black), //253
		VertexFormat(corner + glm::vec3(-4 * h, 6 * h, 0), black), //254
		VertexFormat(corner + glm::vec3(-5 * h, 6*h, 0), black), //255
		VertexFormat(corner + glm::vec3(-5 * h, 7 * h, 0), black), //256
		VertexFormat(corner + glm::vec3(-5 * h, 8 * h, 0), black), //257
		VertexFormat(corner + glm::vec3(-6 * h, 6* h, 0), black),//258
		VertexFormat(corner + glm::vec3(-6 * h, 7 * h, 0), black), //259
		VertexFormat(corner + glm::vec3(-6 * h, 5 * h, 0), black),//260
		VertexFormat(corner + glm::vec3(-7 * h, 5 * h, 0), black), //261
		VertexFormat(corner + glm::vec3(-7 * h, 6 * h, 0), black),//262

		VertexFormat(corner + glm::vec3(-5 * h, 4 * h, 0), white),//263
		VertexFormat(corner + glm::vec3(-5 * h, 5 * h, 0), white)//264
		,VertexFormat(corner + glm::vec3(-6 * h, 4 * h, 0), black),//265

		VertexFormat(corner + glm::vec3(-7 * h, 0 * h, -10), glm::vec3(0.3, 0.9, 1)),//266
		VertexFormat(corner + glm::vec3(9 * h, 0 * h, -10), glm::vec3(0.3, 0.9, 1))//267
		,VertexFormat(corner + glm::vec3(9 * h, 11 * h, -10), glm::vec3(0.3, 0.9, 1))//268
		,VertexFormat(corner + glm::vec3(-7 * h, 11 * h, -10), glm::vec3(0.3, 0.9, 1))//269


	};

	Mesh* PRBird = new Mesh(name);
	std::vector<unsigned short> indices = {	0,1,2,0,2,3,1,4,5,1,5,2,4,7,6,4,7,5,
											8,9,10,8,10,11,9,12,13,9,13,10,12,14,15,12,15,13,
											16,17,18,16,18,19,
											20,21,22,20,22,23,21,24,25,21,25,22,24,26,27,24,27,25,
											28,29,30,28,30,31,29,32,33,29,33,30,32,34,35,32,35,33,
											36,37,38,36,38,39,37,40,41,37,41,38,40,42,43,40,43,41,
											27,44,45,27,45,42,42,45,46,42,46,43,47,31,48,47,48,49,
											48,50,51,48,51,52,50,53,54,50,54,51,53,55,56,53,56,54,55,57,58,55,58,56,
											59,60,61,59,61,62,63,65,64,62,61,66,62,66,67,
											68,69,70,68,70,71,69,72,73,69,73,70,72,74,75,72,75,73,74,62,67,74,67,75,
											76,77,78,76,78,79,77,80,81,77,81,78,80,82,83,80,83,81,
											84,67,85,84,85,86,86,85,87,86,87,88,88,87,89,88,89,90,
											91,90,92,91,92,93,94,93,95,94,95,96,
											97,98,99,97,99,100,101,102,103,101,103,104,105,106,102,105,102,101,
											107,108,106,107,106,105,108,109,110,108,110,106,109,111,112,109,112,110,110,112,113,110,113,114,
											115,116,91,115,91,117,118,119,120,118,120,121,122,105,101,122,101,123,124,107,105,124,105,122,
											125,71,126,125,126,127,128,129,130,128,130,131,132,133,68,132,68,134,
											135,127,136,135,136,137,137,136,118,137,118,138,
											139,128,131,139,131,140,140,131,141,140,141,142,143,139,140,143,140,144,144,140,142,144,142,145,
											145,142,146,145,146,147,147,146,148,147,148,149,151,147,149,151,149,150,152,145,147,152,147,151,
											153,154,155,153,155,156,156,155,157,156,157,158,
											159,160,161,159,161,162,160,163,164,160,164,161,163,123,165,163,165,164,
											166,167,168,166,168,169,169,168,170,169,170,171,168,172,173,168,173,170,172,174,175,172,175,173,
											174,176,177,174,177,175,176,178,179,176,179,177,178,94,96,178,96,179,180,181,159,180,159,182,
											183,158,184,183,184,185,186,187,188,186,188,189,
											190,191,192,190,192,193,194,195,143,194,143,191,195,196,139,195,139,143,196,197,128,196,128,139,
											198,19,132,198,132,199,200,201,153,200,153,202,203,204,205,203,205,206,204,0,3,204,3,205,
											207,208,209,207,209,210,208,8,11,208,11,209,210,209,211,210,211,212,209,11,213,209,213,211,
											11,10,214,11,214,213,10,13,215,10,215,214,212,211,217,212,217,216,211,213,218,211,218,217,213,214,219,213,219,218,
											226,183,185,226,185,223,225,226,223,225,223,222,222,223,220,222,220,224,220,166,169,220,169,221,
											227,180,182,227,182,228,
											229,230,231,229,231,232,230,233,234,230,234,231,232,231,236,232,236,235,231,234,186,231,186,236,
											235,236,238,235,238,237,236,186,189,236,189,238,239,206,240,239,240,241,242,241,243,242,243,244,244,243,245,244,245,246,
											243,247,200,243,200,245,248,210,212,248,212,249,250,244,246,250,246,251,263,229,232,263,232,264,252,253,254,252,254,255,
											255,254,225,255,225,256,256,225,222,256,222,257,260,252,255,260,255,258,258,255,256,258,256,259
											,261,260,258,261,258,262,265,251,252,265,252,260,266,267,268,266,268,269
											
											
	};


	PRBird->InitFromData(vertices, indices);
	return PRBird;
}

Mesh* Object2D::CreateFloor(std::string name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(0, 0, -1), color),
		VertexFormat(corner + glm::vec3(width, 0, -1), color),
		VertexFormat(corner + glm::vec3(width, height, -1), color),
		VertexFormat(corner + glm::vec3(0, height, -1), color)
	};

	Mesh* floor = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 0, 2 };


	floor->InitFromData(vertices, indices);
	return floor;
}







Mesh* Object2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner,  glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	float width = 50;
	float height = 200;
	float diff = 10;
	float miniRect = 40;
	float maxRect = 140;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),//0
		VertexFormat(corner + glm::vec3(width + 2 * diff, 0, 0), color),//1
		VertexFormat(corner + glm::vec3(width + 2 * diff, height/5, 0), color),//2
		VertexFormat(corner + glm::vec3(0, height/5, 0), color),//3

		VertexFormat(corner + glm::vec3(diff, height/5, 0), color),//4
		VertexFormat(corner + glm::vec3(width + diff , height/5, 0), color),//5
		VertexFormat(corner + glm::vec3(diff, miniRect + maxRect, 0), color),//6
		VertexFormat(corner + glm::vec3(width + diff, miniRect + maxRect, 0), color),//7


		VertexFormat(corner + glm::vec3(0, miniRect + maxRect, 0), color),//8
		VertexFormat(corner + glm::vec3(width + 2 * diff, miniRect + maxRect, 0), color),//9
		VertexFormat(corner + glm::vec3(width + 2 * diff, 2*miniRect + maxRect, 0), color),//10
		VertexFormat(corner + glm::vec3(0, 2*miniRect + maxRect, 0), color),//11

	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 0, 2,4,5,7,4,7,6,8,9,10,8,10,11};


	rectangle->InitFromData(vertices, indices);
	return rectangle;
}
