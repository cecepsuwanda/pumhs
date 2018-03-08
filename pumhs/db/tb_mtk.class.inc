<?php
require_once 'default_table.class.inc';
class tb_mtk extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->tablename       = 'tmst_mtk';
        
		$this->fieldlist       = array('NO','thn_sms','gg','fak','prodi','sem','kd_mk','klp_mk','nm_mk','sks_tot','sks_ttm','sks_prk','sks_lpn','syarat','bdg_minat','wp','kd_dsn','flag_p','kd_lab','flag_krs');
        
		$this->sql_orderby     = "";
		
		$this->fieldlist['NO'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>

