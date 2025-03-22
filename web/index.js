Module.onRuntimeInitialized = function() {
    const canvas = document.getElementById('emulator');
    const fileInput = document.getElementById('fileInput');

    Module.canvas = canvas;

    fileInput.addEventListener('change', function(event) {
        const file = event.target.files[0];
        if (file) {
            try {
                let reader = new FileReader();
                reader.onerror = function() {
                    console.error('Failed to read the file.');
                };
                reader.onload = function(e) {
                    const buffer = e.target.result;
                    const byteBuffer = new Uint8Array(buffer);
                    const allocated = Module._malloc(byteBuffer.length);
                    Module.HEAPU8.set(byteBuffer, allocated);
                    Module._LoadROM(allocated, byteBuffer.length);
                    Module._free(allocated);
                    Module._Start();
                };
                reader.readAsArrayBuffer(file);
            } catch (error) {
                console.error('Failed to start emulator: ', error);
            }
        }
    });
}
