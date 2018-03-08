<?php
require_once 'default_table.class.inc';
class tb_fak_jn_prodi extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->sql_select      = 'tmst_fakultas.kd_fakultas,fakultas,kd_prodi,prodi';
		$this->tablename       = 'tmst_fakultas INNER JOIN tmst_prodi ON tmst_fakultas.kd_fakultas=tmst_prodi.kd_fakultas';
       	$this->sql_groupby         = 'kd_fakultas,kd_prodi';
		$this->fieldlist       = array('kd_fakultas','fakultas','kd_prodi','prodi');
              
				
    } // end class constructor

} // end class


?>