var path         = require('path'),
    fs           = require('fs'),
    //errorHandler = require('npm/lib/utils/error-handler'),
    exec         = require('child_process').exec,
    platform     = process.platform,
    arch         = process.arch,
    dependency   = 'appjs-' + platform;

if (platform == "linux") {
  dependency += '-' + arch;
}
fs.exists(__dirname + '/../node_modules/' + dependency, function(exists) {
  if (exists) { return; }
  console.log('Installing '+dependency+' pacakge...');
  exec('npm install '+dependency,{cwd:path.resolve(__dirname,'../../../')},function(err,stdout,stderr){
  
    if(err) {
      console.log('Error installing '+dependency);
      console.log('Please use `npm install '+dependency+' and install the package manually');
    } else {
      console.log(stderr);
    }
  });
});
/*npm.load({}, function(){
  npm.commands.install([dependency], errorHandler);
});*/

