#include "Memory.h"

Memory::Memory(QObject *parent)
    : QObject{parent}
{
    DOLT(this)
#if DELETE_MEMORY_AT_START
    D("removed memory file at start with status: " + BOOL_TO_STR(QFile::remove(MEMORY_FILE)));
#endif
}

Memory::~Memory()
{
    DOLT(this)
}

void Memory::setSerializablePtr(const QSharedPointer<Serializable> &serializablePtr)
{
    if(!m_serializablePtr.isNull())
        W("overwriting serializable object");

    m_serializablePtr = serializablePtr;
}

void Memory::load()
{
    emit this->memoryLoadError("test");
    return;
    if(!QFileInfo::exists( MEMORY_FILE ))
    {
        I("Memory file not exist");
        emit this->memoryFileNotExist();
        return;
    }

    if(m_serializablePtr.isNull())
    {
        W("cannot load memory to non existing serializable object")
        return;
    }

    QFile file( MEMORY_FILE );
    if(!file.open(QIODevice::OpenModeFlag::ReadOnly | QIODevice::OpenModeFlag::Text))
    {
        QString message = "Failed to create memory file: " + file.errorString();
        E(message);
        emit this->memoryLoadError(message);
        return;
    }

    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll(), &jsonParseError);
    file.close();

    if(jsonParseError.error != QJsonParseError::ParseError::NoError)
    {
        QString message = "Failed to parse file to json: " + jsonParseError.errorString();
        E(message);
        emit this->memoryLoadError(message);
        return;
    }

    if(!jsonDocument.isObject()){
        QString message = "Json in file is not a json object";
        E(message);
        emit this->memoryLoadError(message);
        return;
    }

    QJsonObject serializedData = jsonDocument.object();
    QSharedPointer<Serializable> serializablePtr = m_serializablePtr.toStrongRef();
    serializablePtr->deserialize(serializedData);

    I("Memory loaded");
    emit this->memoryLoaded();
}

void Memory::save()
{
    if(m_serializablePtr.isNull())
    {
        W("cannot save memory from non existing serializable object")
        return;
    }

    QFile file( MEMORY_FILE );
    if(!file.open(QIODevice::OpenModeFlag::WriteOnly | QIODevice::OpenModeFlag::Text))
    {
        QString message = "Failed to create memory file: " + file.errorString();
        E(message);
        emit this->memorySaveError(message);
        return;
    }

    QSharedPointer<Serializable> serializablePtr = m_serializablePtr.toStrongRef();
    QJsonObject serializedData = serializablePtr->serialize();
    QJsonDocument jsonDocument(serializedData);

    file.write(jsonDocument.toJson());
    file.close();

    I("Memory saved");
    emit this->memorySaved();
}

bool Memory::debugMemoryFileExist()
{
    QString memoryFile( MEMORY_FILE );
    return QFileInfo::exists(memoryFile);
}

void Memory::debugDeleteMemory()
{
    QString memoryFile( MEMORY_FILE );
    QFile::remove(memoryFile);
}

