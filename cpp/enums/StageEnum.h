#ifndef STAGEENUM_H
#define STAGEENUM_H

enum StageEnum{
    None = 0,
    Configure,
    Play,
    Finish,
};

constexpr StageEnum firstStageEnum = StageEnum::Configure;
constexpr StageEnum lastStageEnum = StageEnum::Finish;

#endif // STAGEENUM_H
