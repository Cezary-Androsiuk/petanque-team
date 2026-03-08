function t(usedArgs = "") {
    /// example parrern:
    /// getStackTrace@qrc:/qt/qml/PetanqueTeam/qml/Trace.js:5
    /// onVerified@qrc:/qt/qml/PetanqueTeam/qml/Main.qml:46
    ///
    /// first should be removed and the second one splitted

    try {
        throw new Error("Stack trace capture");
    } catch (error) {
        var trace = error.stack
        var traceElements = trace.split('\n')

        if(traceElements.length < 2)
        {
            log.e("traceElements length is less than 2", "Trace.js -> get()");
            return
        }

        traceElements.reverse();

        for(var i=0; i<traceElements.length-1; i++)
        {
            var traceElementParts = splitTraceElement(traceElements[i]);
            if(traceElementParts)
            {
                log.t(traceElementParts.filePath,
                      traceElementParts.fileName,
                      traceElementParts.functionName,
                      traceElementParts.lineNumber,
                      i+1,
                      traceElements.length-1,
                      usedArgs)
            }
            else
            {
                log.e("parsing/splitting '"+ traceElements[i] +"' failed", "Trace.js -> get()");
            }
        }
    }
}

function splitTraceElement(stackTraceString) {
    const parts = {};

    const atSignIndex = stackTraceString.indexOf('@');
    if (atSignIndex === -1) {
        log.e("'@' sign in " + stackTraceString + " not found", "Trace.js -> splitTraceElement()");
        return null;
    }
    parts.functionName = stackTraceString.substring(0, atSignIndex);

    const remainingString = stackTraceString.substring(atSignIndex + 1);

    const lastColonIndex = remainingString.lastIndexOf(':');
    if (lastColonIndex === -1) {
        log.e("':' sign in " + stackTraceString + "(trimmed: " + remainingString +
              ") not found", "Trace.js -> splitTraceElement()");
        return null;
    }

    const filePath = remainingString.substring(0, lastColonIndex);
    parts.filePath = filePath;

    const lastSlashInFilePath = filePath.lastIndexOf('/');
    if (lastSlashInFilePath === -1) {
        log.e("'/' sign in " + stackTraceString + "(trimmed: " + filePath +
              ") not found", "Trace.js -> splitTraceElement()");
        return null;
    }
    parts.fileName = filePath.substring(lastSlashInFilePath + 1);


    const lineNumberStr = remainingString.substring(lastColonIndex + 1);

    parts.lineNumber = parseInt(lineNumberStr, 10);

    if (isNaN(parts.lineNumber)) {
        log.e("parsing number '"+lineNumberStr+"' in " + stackTraceString + "(trimmed: " + remainingString +
              ") failed", "Trace.js -> splitTraceElement()");
        return null;
    }

    return parts;
}
