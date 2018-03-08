<?php   
 if(!isset($_SERVER['HTTP_REFERER'])){    
    //exit;
 }
 if (session_status() == PHP_SESSION_NONE) {
   session_start(); 
 }
if(!defined('DS')){
  define('DS', DIRECTORY_SEPARATOR);
  define('ROOT', dirname(__FILE__)); 
}
  
if(!defined('TABLE_CLASS')){  
  define('TABLE_CLASS', ROOT.DS.'pumhs'.DS.'db');
  define('VIEW_CLASS', ROOT.DS.'pumhs'.DS.'view');
  define('DATA_CLASS', ROOT.DS.'pumhs'.DS.'dt');
  define('BASIC_CLASS', ROOT.DS.'basic_class');
  define('PHPExcel', ROOT.DS.'PHPExcel');
  define('DOMPdf', ROOT.DS.'dompdf');
}

function myautoload($className) {
	
   if (file_exists(VIEW_CLASS. DS . strtolower($className) . '.class.inc')) {
		 require_once(VIEW_CLASS. DS . strtolower($className) . '.class.inc');
	 } else {
	 if (file_exists(TABLE_CLASS. DS . strtolower($className) . '.class.inc')) {
		 require_once(TABLE_CLASS. DS . strtolower($className) . '.class.inc');
	 } else {		
				if (file_exists(DATA_CLASS. DS . strtolower($className) . '.class.inc')) {
					require_once(DATA_CLASS. DS . strtolower($className) . '.class.inc');
				} else {		
					   if (file_exists(DOMPdf. DS . strtolower($className) . '_config.inc.php')) {
						   require_once(DOMPdf. DS . strtolower($className) . '_config.inc.php');
					  } else {		   
							if (file_exists(PHPExcel. DS . $className . '.php')) {
								require_once(PHPExcel. DS . $className . '.php');
							} else {
									if (file_exists(BASIC_CLASS. DS . strtolower($className) . '.class.php')) {
										require_once(BASIC_CLASS. DS . strtolower($className) . '.class.php');
									} else {	   
											 if (file_exists(PHPExcel. DS. $className . '.php')) {
												require_once(PHPExcel. DS. $className . '.php');
											 } else {
													 if ((class_exists($className,FALSE)==FALSE) and (strpos($className, 'PHPExcel') == 0)) {
															$ClassFilePath = PHPExcel.DS.str_replace('_',DS,$className).'.php';
															if (file_exists($ClassFilePath)) {
																require_once($ClassFilePath);
															}else {
																   if((strpos($className, 'Stylesheet') !== 0) and (strpos($className, 'Frame_Tree') !== 0)){	
															          echo 'Shared Global Class, Kelas : '.$className.' tidak ditemukan !!!<br>' ; 
									                                } 
																  }  
													 }else {
														  if((strpos($className, 'Stylesheet') !== 0) and (strpos($className, 'Frame_Tree') !== 0)){	
															echo 'Shared Global Class, Kelas : '.$className.' tidak ditemukan !!!<br>' ; 
									                      }
													 }
											 }			               
						   
								}
						   
							}
					  }   
					   
				 }

			}
		}
	
	
}
date_default_timezone_set("Asia/Jakarta");
spl_autoload_register('myautoload');
 
?>