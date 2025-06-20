	/* ------------------------------------------------------------------ */
/*        *-----*                                                             */
/*        | lib |                                                             */
/*        *-----*                                                             */
/*                                                                            */
/*         |  ft_atoi.c  |                                                    */
/*          \-----------/                                                     */
/*                |                                                           */
int			ft_atoi_err(char *arg);/*                                         */
/*               \_/                                                          */
/*                                                                            */
/*         |  ft_is.c  |                                                      */
/*          \---------/                                                       */
/*               |                                                            */
int			ft_isdigit(int c);/*                                              */
int			ft_isspace(int c);/*                                              */
/*              \_/                                                           */
/*                                                                            */
/*         |  ft_len.c  |                                                     */
/*          \----------/                                                      */
/*               |                                                            */
size_t		ft_numlen(long int num);/*                                        */
size_t		ft_strlen(const char *str);/*                                     */
/*                                                                            */
/*         |  ft_mem.c  |                                                     */
/*          \----------/                                                      */
/*               |                                                            */
void		ft_del(void **add);/*                                             */
/*              \_/                                                           */
/*                                                                            */
/*         |  ft_put_fd.c  |                                                  */
/*          \-------------/                                                   */
/*                 |                                                          */
int			ft_putnbr_fd(int n, int fd);/*                                    */
int			ft_putstr_fd(char *str, int fd);/*                                */
/*                \_/                                                         */
/*                                                                            */
/*         |  ft_time.c  |                                                    */
/*          \-----------/                                                     */
/*                |                                                           */
long int	ft_get_time(void);/*                                              */
/*               \_/                                                          */
/*                                                                            */
/*                                                                            */
	/* ------------------------------------------------------------------ */
/*        *------*                                                            */
/*        | srcs |                                                            */
/*        *------*                                                            */
/*                                                                            */
/*         |  cutlery.c  |                                                    */
/*          \-----------/                                                     */
/*                |                                                           */
int			get_cutlery(t_philo *philo);/*                                    */
void		give_cutlery_back(t_philo *philo);/*                              */
/*               \_/                                                          */
/*                                                                            */
/*         |  init.c  |                                                       */
/*          \--------/                                                        */
/*              |                                                             */
t_data		*get_data(void);/*                                                */
void		init(t_args *vals);/*                                             */
/*             \_/                                                            */
/*                                                                            */
/*         |  run_philo.c  |                                                  */
/*          \-------------/                                                   */
/*                 |                                                          */
int			ft_usleep(long int time, t_philo *philo);/*                       */
void		print_mess(t_philo *philo, int mess_index);/*                     */
void		*run_philo(void *index);/*                                        */
/*                \_/                                                         */
/*                                                                            */
/*                                                                            */
	/* ------------------------------------------------------------------ */