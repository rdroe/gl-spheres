let canv = document.querySelector('canvas');
if (!canv) {
    canv = document.createElement('canvas');
    document.body.appendChild(canv);
}
Module['preinitializedWebGLContext'] = canv.getContext('webgl');
console.log('pre js ctx', Module['preinitializedWebGLContext']);
Module['preinitializedWebGLContext'].clearColor(0.9, 0.9, 0.9, 1);
// Module['preinitializedWebGLContext'].enable(Module['preinitializedWebGLContext'].DEPTH_TEST);
