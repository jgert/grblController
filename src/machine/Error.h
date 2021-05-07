//
// Created by Jakub Gert on 07/05/2021.
//

#ifndef GRBL_ERROR_H
#define GRBL_ERROR_H

namespace machine {

    typedef struct Error {
        typedef enum {
            NoError,
            NotSupported,
            InvalidCommandChunkType,
            InvalidCommandNumber,
            UnexpectedChunkType,
            InvalidAddress,
            MissingArguments,
            InvalidArgumentsCount,
        } Error_t;

        uint32_t lineNumber;
        Error_t type;

        explicit Error(uint32_t lineNumber, Error_t type) : lineNumber(lineNumber), type(type) {

        }

        explicit Error() : lineNumber(0), type(NoError) {

        }

        [[nodiscard]] std::string description() const {
            return std::to_string(lineNumber) + ":" + typeDescription(type);
        }

        [[nodiscard]] static std::string typeDescription(Error_t error) {
            switch (error) {
                case NoError:
                    return "no error";
                case NotSupported:
                    return "not supported";
                case InvalidCommandChunkType:
                    return "invalid command chunk type";
                case InvalidCommandNumber:
                    return "invalid command number";
                case UnexpectedChunkType:
                    return "unexpected chunk type";
                case InvalidAddress:
                    return "invalid address";
                case MissingArguments:
                    return "missing arguments";
                case InvalidArgumentsCount:
                    return "invalid arguments count";
            }
        }

    } Error_t;

    inline bool operator==(const Error &lhs, const Error &rhs) {

        return lhs.lineNumber == rhs.lineNumber &&
               lhs.type == rhs.type;
    }

}

#endif //GRBL_ERROR_H
