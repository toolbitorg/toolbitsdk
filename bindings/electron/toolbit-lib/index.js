if(process.platform==='linux') {
  module.exports = require('./lib/tbi-linux.node');
} else if (process.platform==='darwin') {
  module.exports = require('./lib/tbi-macos.node');
} else if (process.platform==='win32') {
  module.exports = require('./lib/tbi-mswin.node');
}
