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
		MsgBoxAssert("���丮 ��ΰ� �ƴմϴ�." + _path);
	}


}

// �ڽ��� ���丮�� ���ϸ� �ֽ��ϴ�.
// Ȯ���ڰ� ����� �� �� ����! �� Ȯ���� ���ͱ���� �׷��� ����
std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(std::vector<std::string> _Ext)
{
	// �� ��ΰ� �� �Ǿ��ִٸ�
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
		std::filesystem::path Ext = Entry.path().extension(); // extension Ȯ���� �̾Ƴ�
		std::string UpperExt = GameEngineString::ToUpperReturn(Ext.string()); // �빮�ڷ� �ٲٰ�

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