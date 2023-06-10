#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

GameEngineDirectory::GameEngineDirectory()
{
}

GameEngineDirectory::~GameEngineDirectory()
{
}

GameEngineDirectory::GameEngineDirectory(const std::string& _path)
	: GameEnginePath(_path)
{
	if (false == IsDirectory())
	{
		MsgBoxAssert("디렉토리 경로가 아닙니다." + _path);
	}


}

// 자신의 디렉토리의 파일만 넣습니다.
// 확장자가 어떤건지 알 수 없다! 즉 확장자 필터기능임 그래서 벡터
std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(std::vector<std::string> _Ext)
{
	// 내 경로가 잘 되어있다면
	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(Path);

	std::vector<std::string> UpperFilter;
	UpperFilter.resize(_Ext.size());

	for (size_t i = 0; i < _Ext.size(); i++)
	{
		UpperFilter.push_back(GameEngineString::ToUpperReturn(_Ext[i]));
	}

	std::vector<GameEngineFile> Result;

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			continue;
		}

		std::filesystem::path Path = Entry.path();
		std::filesystem::path Ext = Entry.path().extension(); // extension 확장자 뽑아냄
		std::string UpperExt = GameEngineString::ToUpperReturn(Ext.string()); // 대문자로 바꾸고

		bool Check = false;

		for (size_t i = 0; i < UpperFilter.size(); i++)
		{
			if (UpperExt == UpperFilter[i])
			{
				Check = true;
				break;
			}
		}

		if (false == Check)
		{
			continue;
		}

		Result.push_back(GameEngineFile(Path.string()));
	}
	return Result;
}