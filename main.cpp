#include <Novice.h>
#include <assert.h>

const char kWindowTitle[] = "LE2B_12_サクライショウセイ_タイトル";

struct Matrix4x4 {
	float m[4][4];
};

struct Vector3 {
	float x, y, z;
};

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

Matrix4x4 MakeTranslateMatrix(const Vector3& traslate);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		Vector3 translate{ 4.1f, 2.6f, 0.8f };
		Vector3 scale{ 1.5f, 5.2f, 7.3f };
		Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
		Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
		Vector3 point{ 2.3f, 3.8f, 1.4f };
		Matrix4x4 transformMatrix = {
			1.0f, 2.0f, 3.0f, 4.0f,
			3.0f, 1.0f, 1.0f, 2.0f,
			1.0f, 4.0f, 2.0f, 3.0f,
			2.0f, 2.0f, 1.0f, 3.0f
		};
		Vector3 transformed = Transform(point, transformMatrix);

		///
		/// ↓更新処理ここから
		///

		VectorScreenPrintf(0, 0, transformed, "transformed");
		MatrixScreenPrintf(0, kRowHeight * 5, translateMatrix);
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, scaleMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& traslate)
{
	Matrix4x4 a;
	a.m[0][0] = 1;
	a.m[0][1] = 0;
	a.m[0][2] = 0;
	a.m[0][3] = 0;

	a.m[1][0] = 0;
	a.m[1][1] = 1;
	a.m[1][2] = 0;
	a.m[1][3] = 0;

	a.m[2][0] = 0;
	a.m[2][1] = 0;
	a.m[2][2] = 1;
	a.m[2][3] = 0;

	a.m[3][0] = traslate.x;
	a.m[3][1] = traslate.y;
	a.m[3][2] = traslate.z;
	a.m[3][3] = 1;
	return a;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 a;
	a.m[0][0] = scale.x;
	a.m[0][1] = 0;
	a.m[0][2] = 0;
	a.m[0][3] = 0;

	a.m[1][0] = 0;
	a.m[1][1] = scale.y;
	a.m[1][2] = 0;
	a.m[1][3] = 0;

	a.m[2][0] = 0;
	a.m[2][1] = 0;
	a.m[2][2] = scale.z;
	a.m[2][3] = 0;

	a.m[3][0] = 0;
	a.m[3][1] = 0;
	a.m[3][2] = 0;
	a.m[3][3] = 1;
	return a;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 b;
	b.x = (vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0]) + (vector.z * matrix.m[2][0]) + (1.0f * matrix.m[3][0]);
	b.y = (vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1]) + (vector.z * matrix.m[2][1]) + (1.0f * matrix.m[3][1]);
	b.z = (vector.x * matrix.m[0][2]) + (vector.y * matrix.m[1][2]) + (vector.z * matrix.m[2][2]) + (1.0f * matrix.m[3][2]);
	float w = (vector.x * matrix.m[0][3]) + (vector.y * matrix.m[1][3]) + (vector.z * matrix.m[2][3]) + (1.0f * matrix.m[3][3]);
	assert(w != 0.0f);
	b.x /= w;
	b.y /= w;
	b.z /= w;
	return b;
}
