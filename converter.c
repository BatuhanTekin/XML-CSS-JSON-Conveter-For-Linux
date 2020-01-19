#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <json/json.h>
#include <libxml/xmlschemastypes.h>

#define MAXCHAR 1000

static char elements[MAXCHAR][MAXCHAR];
static char attributes[MAXCHAR][MAXCHAR];
static void print_element_child(xmlNode * a_node,FILE *fp);
static void add_element_names(xmlNode * a_node);
static void print_element_names(xmlNode * a_node,FILE *fp);
static void add_element_child(xmlNode * a_node);
static int first=0,first1=0,ce = 0,cc=0;
void addchar(char* s, char c) {
       int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

int main(int argc,char *argv[])
{

    

    char buff[256];
    int xmli,xmlj;
    xmlDocPtr doc = NULL;
    xmlNodePtr root_node = NULL, node = NULL , node1 = NULL;
    char ar[MAXCHAR];
    char ar2[MAXCHAR];
    char orderedar[MAXCHAR][MAXCHAR];
    char orderatt[500][500];
    FILE *fp;
    const char s[4]=",";
    const char b[4]="-";
    char* tok;
    int controlpoint = 0,i=0,attcounter=0;
    
if(strcmp(argv[3],"1")==0){
        fp = fopen(argv[1],"r");
     if(fp==NULL){
        puts("error opening file");
        exit(1);
     }
     while(fgets(ar,MAXCHAR,fp)!=NULL){
        
        for(int k = 0; k < sizeof(ar); k++)
     {
        if(ar[k]==(char) 0){
            break;}
      if (ar[k]==',' && ar[k+1]==',')
             {
                     addchar(ar2,ar[k]);
                     addchar(ar2,' ');
             }
            else
            {
                addchar(ar2,ar[k]);
            }                
     }
       tok = strtok(ar2,s);
       while(tok!=NULL){
          strcat(orderedar[i],tok);
          tok = strtok(NULL,s);
          i++;
        }
        controlpoint++;
        if(attcounter==0){
            attcounter=i;
        }
        memset(ar2,0,sizeof(ar2));  
     }
     fclose(fp);
     int attc=0;
     for(int att1=0; att1<attcounter;att1++){
     for(int attt = 0; attt < sizeof(orderedar[att1]); attt++)
     {
        if(orderedar[att1][attt]!=' '){
            addchar(orderatt[attc],orderedar[att1][attt]);
        }
        else{
            addchar(orderatt[attc],'_');
        }
        
     }
     attc++;
     }
     doc = xmlNewDoc(BAD_CAST "1.0");
     root_node = xmlNewNode(NULL,BAD_CAST "root");
     xmlDocSetRootElement(doc,root_node);
     int a = attcounter;
     for (int l = 0 ; l <= controlpoint-2; l++)
     {
            
        sprintf(buff, "node");
        node = xmlNewChild(root_node, NULL, BAD_CAST buff, NULL);
        
         for (int b = 0; b < attcounter; b++) {      
            sprintf(buff,orderedar[a]);
            node1 = xmlNewChild(node, NULL, BAD_CAST orderatt[b],buff);
         a++;
      }
 
      }
    
     xmlSaveFormatFileEnc(argv[2], doc, "UTF-8", 1);
	  xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
     xmlFreeDoc(doc);
     xmlCleanupParser();
     xmlMemoryDump();}
//CSV TO XML */
if(strcmp(argv[3],"5")==0){
    fp = fopen(argv[1],"r");
    if(fp==NULL){
        puts("error opening file");
        exit(1);
    }
 while(fgets(ar,MAXCHAR,fp)!=NULL){
        
        for(int k = 0; k < sizeof(ar); k++)
    {
       
        if(ar[k]==(char) 0){
            break;}
      if (ar[k]==',' && ar[k+1]==',')
             {
                     addchar(ar2,ar[k]);
                     addchar(ar2,' ');
             }
            else
            {
                addchar(ar2,ar[k]);
            }                
    }
       tok = strtok(ar2,s);
       while(tok!=NULL){
          strcat(orderedar[i],tok);
          tok = strtok(NULL,s);
          i++;
        }
        controlpoint++;
        if(attcounter==0){
            attcounter=i;
        }
        memset(ar2,0,sizeof(ar2)); 
         
    }
    fclose(fp);
    int a1=attcounter;
    json_object *jarray = json_object_new_array();
    for(int aj = 0; aj < controlpoint-1 ; aj++)
    {
        json_object * jobj = json_object_new_object();
        for(int bj=0 ; bj < attcounter ; bj++ )  {
        json_object *jstring2 = json_object_new_string(orderedar[a1]);
        json_object_object_add(jobj,orderedar[bj], jstring2);
        a1++;}

        json_object_array_add(jarray,jobj);
    }
    json_object_to_file(argv[2],jarray);}
//CSV TO JSON 
if(strcmp(argv[3],"2")==0){
     FILE * fp;
    xmlDoc *doc1 = NULL;
    xmlNode *root_element = NULL;
    
    const char *Filename = argv[1];
    doc1 = xmlReadFile(Filename, NULL, 0);
    if (doc1 == NULL)
    {
        printf("error: could not parse file %s\n", Filename);
    }
    else
    {    
          root_element = xmlDocGetRootElement(doc1);
          fp = fopen(argv[2],"w");
          print_element_names(root_element,fp);
          print_element_child(root_element,fp);
          xmlFreeDoc(doc1);
    }
    
    xmlCleanupParser();
    fclose(fp); }
//XML TO CSV 
if(strcmp(argv[3],"3")==0){

    xmlDoc *doc2 = NULL;
    xmlNode *root_element1 = NULL;
    
    const char *Filename = argv[1];
    doc2 = xmlReadFile(Filename, NULL, 0);
    if (doc2 == NULL)
    {
        printf("error: could not parse file %s\n", Filename);
    }
    else
    {    
          root_element1 = xmlDocGetRootElement(doc2);
          add_element_names(root_element1);
          add_element_child(root_element1);
          xmlFreeDoc(doc2);
    }
    int a2=1;
   json_object *jarray = json_object_new_array();
   for(int ak = 0; ak < (cc/ce) ; ak++)
    {
        json_object * jobj = json_object_new_object();
        for(int bk=1 ; bk < ce ; bk++ )  {
        json_object *jstring2 = json_object_new_string(attributes[a2]);
        json_object_object_add(jobj,elements[bk], jstring2);
        a2++;}
        json_object_array_add(jarray,jobj);
        a2++;
    }
    json_object_to_file(argv[2],jarray);
    xmlCleanupParser(); }
//XML TO Json*/
if(strcmp(argv[3],"7")==0){

    xmlDocPtr doc5;
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt;
    
    char *XMLFileName = argv[1];
    char *XSDFileName = argv[2];
   
    
    xmlLineNumbersDefault(1); 
    ctxt = xmlSchemaNewParserCtxt(XSDFileName); 
    schema = xmlSchemaParse(ctxt); 
    xmlSchemaFreeParserCtxt(ctxt); 
    
    doc5 = xmlReadFile(XMLFileName, NULL, 0); 
    if (doc5 == NULL)
    {
        fprintf(stderr, "Could not parse %s\n", XMLFileName);
    }
    else
    {
        xmlSchemaValidCtxtPtr ctxt; 
        int ret;
        
        ctxt = xmlSchemaNewValidCtxt(schema); 
        ret = xmlSchemaValidateDoc(ctxt, doc5); 
        if (ret == 0) 
        {
            printf("%s validates\n", XMLFileName);
        }
        else if (ret > 0) 
        {
            printf("%s fails to validate\n", XMLFileName);
        }
        else 
        {
            printf("%s validation generated an internal error\n", XMLFileName);
        }
        xmlSchemaFreeValidCtxt(ctxt); 
        xmlFreeDoc(doc5);
    }
    
    if(schema != NULL)
        xmlSchemaFree(schema); 

    xmlSchemaCleanupTypes(); 
    xmlCleanupParser(); 
    xmlMemoryDump();}
//XSD
    free(tok);
    free(fp);
    
        return 0 ;
}
 void print_element_names(xmlNode * a_node,FILE *fp)
{   FILE *c =fp;
    char a[10]="root";
    char nodeholder[100];
    int nodecount=0;
    xmlNode *cur_node = NULL;
    
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
       
        if (cur_node->type == XML_ELEMENT_NODE) {
           if(strcmp(cur_node->name,a) !=0){  
               if(nodecount==0){
                   strcat(nodeholder,cur_node->name);
                   nodecount++;
               }
               if(strcmp(nodeholder,cur_node->name)!= 0 && first==0){
            fprintf(c,"%s ", cur_node->name);
            first=1;}
            else if (strcmp(nodeholder,cur_node->name)== 0 && first!=0){
            break;
            }
            else
            {if(strcmp(nodeholder,cur_node->name)!= 0)
                fprintf(c,"%s ", cur_node->name);
            }
            
            }
           
        }
        print_element_names(cur_node->children,c);
    }
}
 void print_element_child(xmlNode * a_node,FILE *fp)
{   FILE *c =fp;
    char a[10]="root";
    char nodeholder[100];
    int nodecount=0;
    xmlNode *cur_node = NULL;
    
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
           if(strcmp(cur_node->name,a) !=0){  
               if(nodecount==0){
                   strcat(nodeholder,cur_node->name);
                   nodecount++;
               }
            fprintf(c,"%s ", cur_node->children->content);
            }
           
        }
        print_element_child(cur_node->children,c);
    }
}
static int nodecount1=0;
static void add_element_names(xmlNode * a_node){
    char a[10]="root";
    char nodeholder[100];
    
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
       
        if (cur_node->type == XML_ELEMENT_NODE) {
           if(strcmp(cur_node->name,a) !=0){  
               if(nodecount1==0){
                   strcat(nodeholder,cur_node->name);
                   nodecount1++;
               }
               if(strcmp(nodeholder,cur_node->name)!= 0 && first1==0){
                   strcat(elements[ce],cur_node->name);
                //  printf("%d",ce);
                //  printf("%s \n",elements[ce]);
                   ce++;
            first1=1;}
            else if (strcmp(nodeholder,cur_node->name)== 0 && first1!=0){
            break;
            }
            else
            {if(strcmp(nodeholder,cur_node->name)!= 0)
                strcat(elements[ce],cur_node->name);
               // printf("%d",ce);
               // printf("%s \n",elements[ce]);
                   ce++;
            }
            
            }
           
        }
        add_element_names(cur_node->children);
    }
}
static int nodecount2=0;
static void add_element_child(xmlNode * a_node){
    char a[10]="root";
    char nodeholder[100];
    
    xmlNode *cur_node = NULL;
    
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
           if(strcmp(cur_node->name,a) !=0){  
               if(nodecount2==0){
                   strcat(nodeholder,cur_node->name);
                   nodecount2++;
               }
            strcat(attributes[cc],cur_node->children->content);
              //    printf("%d ",cc);                 
               //   printf("%s \n",attributes[cc]);
                   cc++;
            }
           
        }
        add_element_child(cur_node->children);
    }
}
