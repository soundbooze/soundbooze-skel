const execFile = require('child_process').execFile;

const program = 'gcc';
const child = execFile(program, ['--version'], (error, stdout, stderr) => {
    if (error) {
        console.error('stderr', stderr);
        throw error;
    }
    console.log(stdout);
});
